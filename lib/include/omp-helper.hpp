#pragma once

#ifdef _OPENMP

#include <omp.h>

#endif

namespace omp {

inline int getThreadNumber() {
#if defined(_OPENMP) and not defined(CellularAutomata_NoOpenMP)
    return omp_get_thread_num();
#else
    return 0; // Always report the master thread number
#endif
}

inline int getMaxThreads() {
#if defined(_OPENMP) and not defined(CellularAutomata_NoOpenMP)
#ifdef CellularAutomata_MaxThreads
    int ompValue = omp_get_max_threads();
    return CellularAutomata_MaxThreads > ompValue ? ompValue : CellularAutomata_MaxThreads;
#else
    return omp_get_max_threads();
#endif
#else
    return 1;
#endif
}

inline void setNumThreads(int numThreads) {
#if defined(_OPENMP) and not defined(CellularAutomata_NoOpenMP)
    omp_set_num_threads(numThreads);
#endif
}

inline bool inParallel() {
#if defined(_OPENMP) and not defined(CellularAutomata_NoOpenMP)
    return static_cast<bool>(omp_in_parallel());
#else
    return false;
#endif
}

}
