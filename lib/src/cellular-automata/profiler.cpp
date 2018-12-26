#include "cellular-automata/profiler.hpp"

#include <sstream>

using namespace std;

namespace profiler {
Threads::Threads() {
    Profiler::get().enterThreadedSection();
}

Threads::~Threads() {
    Profiler::get().exitThreadedSection();
}

std::string Section::path() const {
    if (m_parent) {
        return m_parent->path() + "." + m_name;
    }
    return m_name;
}

duration_type Section::time() const {
    return m_duration;
}

Section::Section()
    : m_type(Type::ROOT), m_parent(nullptr), m_name("root") {}

Section::Section(Section::Type type, Section * parent, const string & name)
    : m_type(type), m_parent(parent), m_name(name) {
}

Section::~Section() {
    for (auto child : m_children) {
        delete child;
    }
}

void Section::visit(section_visitor_type visitor) const {
    visitor(*this);
    for (auto child : m_children) {
        child->visit(visitor);
    }
}

Section * Section::appendChild(Section::Type type, const string & name) {
    for (auto child : m_children) {
        if (child->m_name == name) {
            if (child->m_type != type) {
                throw std::logic_error("Type mismatch for sections with same name");
            }

            return child;
        }
    }
    m_children.emplace_back(new Section(type, this, name));
    return m_children.back();
}

Section * Section::getParent() const {
    return m_parent;
}

void Section::addDuration(profiler::duration_type timeSpent) {
    lock_guard<mutex> lock(m_durationMutex);

    m_duration += timeSpent;
}

void Section::reset() {
    for (auto child : m_children) {
        delete child;
    }
    m_children.clear();
    m_duration = duration_type(0);
}

Profiler::Profiler()
    : m_root(), m_currentSection(&m_root) {}

Profiler & Profiler::get() {
    static Profiler instance;

    return instance;
}

void Profiler::reset() {
    m_root.reset();
}

void Profiler::collect(section_visitor_type visitor) const {
    m_root.visit(std::move(visitor));
}

void Profiler::pushSection(const string & name, Section::Type type) {
    getCurrentSection() = getCurrentSection()->appendChild(type, name);
}

void Profiler::popSection(duration_type timeSpent) {
    Section *& currentSection = getCurrentSection();

    if (m_threaded) {
        if (currentSection == m_currentSection) {
            throw std::logic_error("Cannot pop a section past the start of a threaded section");
        }
    } else {
        if (currentSection == &m_root) {
            throw std::logic_error("Cannot pop the root section!");
        }
    }

    currentSection->addDuration(timeSpent);

    currentSection = currentSection->getParent();
}

void Profiler::enterThreadedSection() {
    if (m_threaded) {
        throw std::logic_error("Cannot enter a threaded section twice");
    }

    m_threaded = true;
    ++m_threadSequence;
    m_threadSection = m_currentSection;
}

void Profiler::exitThreadedSection() {
    if (!m_threaded) {
        throw std::logic_error("Cannot exit a threaded section before entering one");
    }

    m_threaded = false;
}

void Profiler::setCurrentSection(Section & section) {
    getCurrentSection() = &section;
}

Section *& Profiler::getCurrentSection() {
    thread_local static uint64_t sequence = 0;
    thread_local static Section * section = nullptr;

    if (m_threaded) {
        if (section == nullptr || sequence != m_threadSequence) {
            section = m_threadSection;
            sequence = m_threadSequence;
        }

        return section;
    } else {
        return m_currentSection;
    }
}
}
