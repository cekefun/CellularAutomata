set(GPUSOURCES
    GameOfLife.cpp
    Initialize.cpp
    )

add_library(gpulib ${GPUSOURCES})
target_compile_definitions(gpulib PUBLIC BY_ROW)
target_include_directories(gpulib PRIVATE ${OpenCL_INCLUDE_DIRS})
target_link_libraries(gpulib ${OpenCL_LIBRARIES})
