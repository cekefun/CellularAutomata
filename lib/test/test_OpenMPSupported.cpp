#include "omp-helper.hpp"

#include <gtest/gtest.h>

TEST(OpenMP, Supported) {
#ifndef _OPENMP
    GTEST_FATAL_FAILURE_("OpenMP support is not enabled in this environment");
#else

    omp::setNumThreads(omp::getMaxThreads());

    int numThreads = 0;
    int numThreads2 = 0;

#pragma omp parallel reduction(+:numThreads)
    {
        EXPECT_TRUE(omp::inParallel());

        ++numThreads;

#pragma omp critical
        {
            ++numThreads2;
        }
    }

    EXPECT_EQ(omp::getMaxThreads(), numThreads);
    EXPECT_EQ(omp::getMaxThreads(), numThreads2);
#endif
}
