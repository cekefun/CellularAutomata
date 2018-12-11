#pragma once

#include <cstdint>
#include <chrono>
#include <functional>
#include <list>
#include <string>
#include <mutex>

#define PROFILER_RESET profiler::Profiler::get().reset()

#define PROFILER_COLLECT(ARG_VARIABLE) profiler::Profiler::get().collect(ARG_VARIABLE)

#define PROFILER_METHOD(ARG_NAME) profiler::SectionMethod _profilerMethod(ARG_NAME)

#define PROFILER_BLOCK(ARG_NAME) profiler::SectionBlock _profilerBlock ## __LINE__(ARG_NAME)

#define PROFILER_THREADS profiler::Threads _profilerThread ## __LINE__

namespace profiler {
using clock_type = std::chrono::steady_clock;
using duration_type = clock_type::duration;
using time_point_type = clock_type::time_point;

class Profiler;

class Section;

using section_visitor_type = std::function<void(const Section &)>;

class Section {
    friend class Profiler;

public:
    enum class Type : std::uint8_t {
        ROOT, METHOD, BLOCK
    };

    std::string path() const;

    duration_type time() const;

protected:
    Section();

    Section(Type type, Section * parent, const std::string & name);

    ~Section();

    void visit(section_visitor_type visitor) const;

    Section * appendChild(Type type, const std::string & name);

    Section * getParent() const;

    void addDuration(duration_type timeSpent);

    void reset();

private:
    Type m_type;
    Section * m_parent;
    std::string m_name;
    // List instead of vector because pointers to list elements don't get invalidated on append
    std::list<Section *> m_children = {};

    duration_type m_duration = {};
    std::mutex m_durationMutex = {};
};

template<Section::Type T>
class TypedSection;

class Threads;

class Profiler {
private:
    Profiler();

public:
    static Profiler & get();

    Profiler(const Profiler &) = delete;

    Profiler(Profiler &&) = delete;

    Profiler & operator=(const Profiler &) = delete;

    Profiler & operator=(Profiler &&) = delete;

    void reset();

    void collect(section_visitor_type visitor) const;

    void pushSection(const std::string & name, Section::Type type);

    void popSection(duration_type timeSpent);

    void enterThreadedSection();

    void exitThreadedSection();

private:
    void setCurrentSection(Section & section);

    Section *& getCurrentSection();

    Section m_root;
    Section * m_currentSection;

    bool m_threaded = false;
    std::uint64_t m_threadSequence = 0;
    Section * m_threadSection = nullptr;
};

template<Section::Type T>
class TypedSection {
public:
    explicit TypedSection(const std::string & name) : m_begin(clock_type::now()) {
        Profiler::get().pushSection(name, T);
    }

    ~TypedSection() {
        Profiler::get().popSection(clock_type::now() - m_begin);
    }

    TypedSection(const TypedSection<T> &) = delete;

    TypedSection(TypedSection<T> &&) = delete;

    TypedSection & operator=(const TypedSection<T> &) = delete;

    TypedSection & operator=(TypedSection<T> &&) = delete;

private:
    const time_point_type m_begin;
};

using SectionMethod = TypedSection<Section::Type::METHOD>;
using SectionBlock = TypedSection<Section::Type::BLOCK>;

class Threads {
public:
    Threads();

    ~Threads();

    Threads(const Threads &) = delete;

    Threads(Threads &&) = delete;

    Threads & operator=(const Threads &) = delete;

    Threads & operator=(Threads &&) = delete;
};

}
