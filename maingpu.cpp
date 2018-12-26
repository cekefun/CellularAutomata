#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.hpp>
#else
#include <CL/cl.hpp>
#endif

#include <iostream>
#include <array>
#include <fstream>
#include "gpu/Initialize.cpp"
int main(){
    //cl::Program program = CreateProgram("../gpu/ProcessMultiArray.cl");
    cl::Program program = CreateProgram("../gpu/ProcessByRow.cl");

    cl::Context context = program.getInfo<CL_PROGRAM_CONTEXT>();
    auto devices = context.getInfo<CL_CONTEXT_DEVICES>();
    cl::Device& device = devices.front();

    const int numRows = 3;
    const int numCols = 3;
    const int count = numRows*numCols;
    std::array<std::array<int, numCols>, numRows> arr =         {{{0,1,0},
                                                                 {0,1,0},
                                                                 {0,1,0}}};
    std::array<std::array<int, numCols>, numRows> target =      {{{0,1,0},
                                                                   {0,1,0},
                                                                   {0,1,0}}};

    cl::Kernel kernel(program,"ProcessMultiArray");

    // Just allocate a target matrix
    cl::Buffer bufTarget(context, CL_MEM_READ_WRITE|CL_MEM_HOST_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(int)*count,target.data());
    kernel.setArg(1, bufTarget);

    // Set the amount of rows
    //kernel.setArg(2,numRows);

    for(int i= 0; i< 3; i++){
        // Load in current matrix
        cl::Buffer buf(context, CL_MEM_READ_WRITE|CL_MEM_HOST_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(int)*count,arr.data());

        kernel.setArg(0, buf);


        cl::CommandQueue queue(context,device);
        queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(numRows, numCols));
        //queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(numRows));

        queue.enqueueReadBuffer(bufTarget,1002,0, sizeof(int)*count,arr.data());

        std::cout<< i<<std::endl;
        for (auto j: arr){
            for (auto k: j){
                std::cout<<k;
//                if (k == 0){
//                    std::cout<< ".";
//                }
//                else if (k == 1){
//                    std::cout<<"0";
//                }
//                else{
//                    std::cout<<k;
//                }

            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }

}