//
// Created by cekef on 31-Oct-18.
//
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#elif __linux__
#include <CL/cl2.hpp>
#else
#include <CL/cl.hpp>
#endif
#include <iostream>
#include <fstream>
#include <utility>
#include "GameOfLife.h"
cl::Program CreateProgram(const std::string& filename){
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    if(all_platforms.empty()){
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];

    std::cout << "Using platform: "<<default_platform.getInfo<CL_PLATFORM_NAME>()<<"\n";

    //Find device
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
    if(all_devices.empty()){
        std::cout<<" No devices found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Device default_device=all_devices[0];
    std::cout<< "Using device: "<<default_device.getInfo<CL_DEVICE_NAME>()<<"\n";

    //std::ifstream programFile(filename);
    //std::string src(std::istreambuf_iterator<char>(programFile), (std::istreambuf_iterator<char>()));

    GameOfLife gol;
    std::string src = gol.Compile();
    std::cout<<src<<std::endl;

#if defined(__APPLE__) || defined(__MACOSX)
    cl::Program::Sources sources(1,std::make_pair(src.c_str(),src.length()+1));
#else
    cl::Program::Sources sources;

    sources.push_back(std::make_pair(src.data(),src.size()));
#endif

    cl::Context context(default_device);
    cl::Program program(context,sources);

    if(program.build({default_device})!=CL_SUCCESS){
        std::cout<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device)<<"\n";
        exit(1);
    }


    return program;

}
