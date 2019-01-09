
set(GPUSOURCES
        GameOfLife.cpp
        Initialize.cpp
        )

include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

add_library(gpulib ${GPUSOURCES})
target_link_libraries (gpulib ${OpenCL_LIBRARY})