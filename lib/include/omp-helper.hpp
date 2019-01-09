#pragma once

#ifdef _OPENMP

#include <omp.h>

#endif

namespace omp {

inline int getThreadNumber() {
#ifdef _OPENMP
    return omp_get_thread_num();
#else
    return 0; // Always report the master thread number
#endif
}

inline int getMaxThreads() {
#ifdef _OPENMP
    return omp_get_max_threads();
#else
    return 1;
#endif
}

inline void setNumThreads(int numThreads) {
#ifdef _OPENMP
    omp_set_num_threads(numThreads);
#endif
}

inline bool inParallel() {
#ifdef _OPENMP
    return static_cast<bool>(omp_in_parallel());
#else
    return false;
#endif
}

}
