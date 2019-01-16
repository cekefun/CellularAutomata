set(GPUSOURCES
    GameOfLife.cpp
        )

add_library(gpulibnaive ${GPUSOURCES} CompileNaive.cpp)
target_include_directories(gpulibnaive PRIVATE ${OpenCL_INCLUDE_DIRS})
target_link_libraries(gpulibnaive ${OpenCL_LIBRARIES})

add_library(gpulibbyrow ${GPUSOURCES} CompileByRow.cpp)
target_include_directories(gpulibbyrow PRIVATE ${OpenCL_INCLUDE_DIRS})
target_link_libraries(gpulibbyrow ${OpenCL_LIBRARIES})
