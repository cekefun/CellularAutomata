#pragma once

#include <cstdint>
#include <chrono>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#ifndef PROFILER_ENABLED
#define PROFILER_ENABLED false
#endif

#define PROFILER_MODE_COMBINE true
#define PROFILER_MODE_SEPARATE false

#if PROFILER_ENABLED
#define _PROFILER_HELPER_CONCAT(ARG_LHS, ARG_RHS) ARG_LHS ## ARG_RHS
#define _PROFILER_HELPER_CONCAT2(ARG_LHS, ARG_RHS) _PROFILER_HELPER_CONCAT(ARG_LHS, ARG_RHS)

#define PROFILER_BLOCK(ARG_NAME, ARG_THREAD)\
static ::profiler::Section _PROFILER_HELPER_CONCAT2(_section, __LINE__)(ARG_NAME, __FILE__, __LINE__);\
::profiler::ActiveSection _PROFILER_HELPER_CONCAT2(_activeSection, __LINE__)(_PROFILER_HELPER_CONCAT2(_section, __LINE__), ARG_THREAD)
#else
#define PROFILER_BLOCK(ARG_NAME, ARG_THREAD)
#endif

namespace profiler {
using clock_type = std::chrono::steady_clock;
using duration_type = clock_type::duration;
using time_point_type = clock_type::time_point;

class ActiveSection;

class Profiler;

class Section;

using section_visitor_type = std::function<void(const Section &)>;

class Section {
    friend class ActiveSection;

    friend class Profiler;

    struct PerThread {
        std::size_t m_timesRun { 0 };
        std::list<duration_type> m_durations {};
        duration_type m_combinedTime { 0 };
    };

public:
    inline const std::string & name() const noexcept {
        return m_name;
    }

    const std::list<duration_type> & durations() const;

    duration_type duration() const;

    std::size_t num_calls() const noexcept;

    std::size_t num_threads() const noexcept;

    Section(const char * name, const char * filename, std::size_t lineNumber);

protected:
    void visit(section_visitor_type visitor) const;

    void addDuration(duration_type timeSpent, std::uint32_t threadNumber);

    void reset();

    void ensureThreadUsable(std::size_t threadId);

    void setMode(bool combine);

private:
    const std::string m_name;
    const std::string m_filename;
    const std::size_t m_lineNumber;

    bool m_combine = false;

    mutable std::vector<PerThread> m_perThread {};
    mutable std::list<duration_type> m_mergedDurations {};

    mutable std::mutex m_mutex {};
};

class Profiler {
    friend class Section;

public:
    static Profiler & get() noexcept;

    Profiler(const Profiler &) = delete;

    Profiler(Profiler &&) = delete;

    Profiler & operator=(const Profiler &) = delete;

    Profiler & operator=(Profiler &&) = delete;

    void reset();

    void collect(section_visitor_type visitor) const;

    void setMaxThreads(std::size_t maxThreads);

    void setMode(bool combine);

protected:
    void listSection(Section * section);

private:
    Profiler() = default;

    std::map<std::string, Section *> m_sections {};
    mutable std::mutex m_mutex {};

    std::size_t m_maxThreads = 1;
    bool m_combine = false;
};

class ActiveSection {
public:
    inline ActiveSection(Section & section, std::uint32_t threadNumber) noexcept
        : m_begin(clock_type::now()),
          m_section(section),
          m_threadNumber(threadNumber) {}

    inline ActiveSection(Section & section, int threadNumber) noexcept
        : ActiveSection(section, static_cast<std::uint32_t>(threadNumber)) {}

    inline ~ActiveSection() {
        m_section.addDuration(clock_type::now() - m_begin, m_threadNumber);
    }

    ActiveSection(const ActiveSection &) = delete;

    ActiveSection(ActiveSection &&) = delete;

    ActiveSection & operator=(const ActiveSection &) = delete;

    ActiveSection & operator=(ActiveSection &&) = delete;

private:
    const time_point_type m_begin;
    Section & m_section;
    const std::uint32_t m_threadNumber;
};
}
