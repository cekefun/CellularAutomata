#include <gtest/gtest.h>
#include <omp.h>

TEST(OpenMP, Supported) {
#ifndef _OPENMP
    GTEST_FATAL_FAILURE_("OpenMP support is not enabled in this environment");
#else

    omp_set_num_threads(omp_get_max_threads());

    int numThreads = 0;
    int numThreads2 = 0;

#pragma omp parallel reduction(+:numThreads)
    {
        EXPECT_TRUE(omp_in_parallel());

        ++numThreads;

#pragma omp critical
        {
            ++numThreads2;
        }
    }

    EXPECT_EQ(omp_get_max_threads(), numThreads);
    EXPECT_EQ(omp_get_max_threads(), numThreads2);
#endif
}
