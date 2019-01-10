#include "cellular-automata/profiler.hpp"

#include <omp.h>

using namespace std;

namespace profiler {
const std::list<duration_type> & Section::durations() const {
    std::lock_guard<std::mutex> lock(m_mutex);

    for (auto & thread : m_perThread) {
        m_mergedDurations.splice(m_mergedDurations.end(), thread.m_durations);

        if (thread.m_combinedTime.count() > 0) {
            m_mergedDurations.emplace_back(thread.m_combinedTime);
            thread.m_combinedTime = duration_type::zero();
        }
    }

    return m_mergedDurations;
}

duration_type Section::duration() const {
    const std::list<profiler::duration_type> & durations = this->durations();
    profiler::duration_type totalDuration(0);

    for (const auto & val : durations) {
        totalDuration += val;
    }

    return totalDuration;
}

std::size_t Section::num_calls() const noexcept {
    std::size_t result = 0;

    for (auto & thread : m_perThread) {
        result += thread.m_timesRun;
    }

    return result;
}

std::size_t Section::num_threads() const noexcept {
    std::size_t result = 0;

    for (auto & thread : m_perThread) {
        if (thread.m_timesRun > 0) {
            ++result;
        }
    }

    return result;
}

Section::Section(const char * name, const char * filename, std::size_t lineNumber)
    : m_name(name),
      m_filename(filename),
      m_lineNumber(lineNumber) {
    Profiler::get().listSection(this);
}

void Section::visit(section_visitor_type visitor) const {
    visitor(*this);
}

void Section::addDuration(profiler::duration_type timeSpent, std::uint32_t threadNumber) {
    ++m_perThread[threadNumber].m_timesRun;
    if (m_combine) {
        m_perThread[threadNumber].m_combinedTime += timeSpent;
    } else {
        m_perThread[threadNumber].m_durations.emplace_back(timeSpent);
    }
}

void Section::reset() {
    std::lock_guard<std::mutex> lock(m_mutex);

    m_perThread.clear();
    m_mergedDurations.clear();
}

void Section::ensureThreadUsable(std::size_t threadId) {
    if (threadId < m_perThread.size()) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_mutex);

    m_perThread.resize(threadId + 1);
}

void Section::setMode(bool combine) {
    std::lock_guard<std::mutex> lock(m_mutex);

    m_combine = combine;
}

Profiler & Profiler::get() noexcept {
    static Profiler instance;

    return instance;
}

void Profiler::reset() {
    std::lock_guard<std::mutex> lock(m_mutex);

    for (const auto & entry : m_sections) {
        entry.second->reset();
        entry.second->ensureThreadUsable(m_maxThreads);
        entry.second->setMode(m_combine);
    }
}

void Profiler::collect(section_visitor_type visitor) const {
    std::lock_guard<std::mutex> lock(m_mutex);

    for (const auto & entry : m_sections) {
        entry.second->visit(visitor);
    }
}

void Profiler::setMaxThreads(std::size_t maxThreads) {
    m_maxThreads = maxThreads;

    std::lock_guard<std::mutex> lock(m_mutex);

    for (const auto & entry : m_sections) {
        entry.second->ensureThreadUsable(m_maxThreads);
    }
}

void Profiler::setMode(bool combine) {
    m_combine = combine;

    std::lock_guard<std::mutex> lock(m_mutex);

    for (const auto & entry : m_sections) {
        entry.second->setMode(combine);
    }
}

void Profiler::listSection(profiler::Section * section) {
    std::lock_guard<std::mutex> lock(m_mutex);

    m_sections.emplace(section->name(), section);
    section->ensureThreadUsable(m_maxThreads);
    section->setMode(m_combine);
}
}
