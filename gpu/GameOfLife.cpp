//
// Created by cekef on 13-Dec-18.
//
#include "GameOfLife.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>


void GameOfLife::setInitialData(const std::vector<std::vector<int> >& newData) {
    rows = newData.size();
    cols = newData[0].size();
    data.clear();
    for(auto& i: newData){
        data.insert(data.end(),i.begin(),i.end());
    }
    Initialize();
}

std::vector<std::vector<int> > GameOfLife::getData() {
    std::vector<std::vector<int> > result;
    for(int i= 0; i<rows; i++){
        result.emplace_back(std::vector<int>(data.begin() + (i*cols), data.begin()+(i+1)*cols));
    }
    return result;
}

void GameOfLife::addDefaultPattern(int state, int newState) {
    if(pattern.find(state)== pattern.end()){
           pattern[state] = std::map<std::vector<int >, int>();
    }
    pattern[state][{}] = newState;
}

void GameOfLife::addDirectPattern(int state, int newState, int value) {
    if(pattern.find(state)== pattern.end()){
        pattern[state] = std::map<std::vector<int >, int>();
    }
    pattern[state][{value}] = newState;
}

void GameOfLife::addRangePattern(int state, int newState, int minRange, int maxRange) {
    if(minRange>maxRange){
        return;
    }
    if(pattern.find(state)== pattern.end()){
        pattern[state] = std::map<std::vector<int >, int>();
    }
    pattern[state][{minRange,maxRange}] = newState;
}

void GameOfLife::addRangePatternNegInfinity(int state, int newState, int maxRange) {
    if(pattern.find(state)== pattern.end()){
        pattern[state] = std::map<std::vector<int >, int>();
    }
    pattern[state][{std::numeric_limits<int>::infinity(),maxRange}] = newState;
}

void GameOfLife::addRangePatternPosInfinity(int state, int newState, int minRange) {
    if(pattern.find(state)== pattern.end()){
        pattern[state] = std::map<std::vector<int >, int>();
    }
    pattern[state][{minRange,std::numeric_limits<int>::infinity()}] = newState;
}

std::string GameOfLife::generateEnding(std::string stateName) const {
    std::string result;
    bool started = false;
    for (auto i: pattern) {
        if(! started){
            result += " if (" + stateName + " == " + std::to_string(i.first) + "){";
            started = true;
        }else{
            result += "else if (" + stateName + " == " + std::to_string(i.first) + "){";
        }

        if (!i.second.empty() || i.second.find({}) == i.second.end()) {
            bool done = false;
            for (auto &j: i.second) {
                // First the match patterns
                if (j.first.size() == 1) {
                    if (done) {
                        result += "else if( neighbours == " + std::to_string(j.first.front()) + "){target[id] = " +
                                  std::to_string(j.second) + ";}";
                    } else {
                        result += "if( neighbours == " + std::to_string(j.first.front()) + "){target[id] = " +
                                  std::to_string(j.second) + ";}";
                        done = true;
                    }
                }
            }
            for (auto &j: i.second) {
                // Then the range patterns
                if (j.first.size() == 2) {
                    if (j.first.front() == std::numeric_limits<int>::infinity()) {
                        if (done) {
                            result +=
                                    "else if( neighbours <= " + std::to_string(j.first.back()) + "){target[id] = " +
                                    std::to_string(j.second) + ";}";
                        } else {
                            result += "if( neighbours <= " + std::to_string(j.first.back()) + "){target[id] = " +
                                      std::to_string(j.second) + ";}";
                            done = true;
                        }
                    } else if (j.first.back() == std::numeric_limits<int>::infinity()) {
                        if (done) {
                            result += "else if( neighbours >= " + std::to_string(j.first.front()) +
                                      "){target[id] = " +
                                      std::to_string(j.second) + ";}";
                        } else {
                            result += "if( neighbours >= " + std::to_string(j.first.front()) + "){target[id] = " +
                                      std::to_string(j.second) + ";}";
                            done = true;
                        }
                    } else {
                        if (done) {
                            result +=
                                    "else if( neighbours >= " + std::to_string(j.first.front()) +
                                    " && neighbours <= " +
                                    std::to_string(j.first.back()) + "){target[id] = " + std::to_string(j.second) +
                                    ";}";
                        } else {
                            result +=
                                    "if( neighbours >= " + std::to_string(j.first.front()) + " && neighbours <= " +
                                    std::to_string(j.first.back()) + "){target[id] = " + std::to_string(j.second) +
                                    ";}";
                            done = true;
                        }
                    }
                }
            }
            if (i.second.find({}) != i.second.end()) {
                result += "else{ target[id] = " + std::to_string(i.second[{}]) + ";}";
            } else {
                result += "else{ target[id] = data[id];}";
            }
        } else if (i.second.find({}) != i.second.end()) {
            result += "target[id] = " + std::to_string(i.second[{}]) + ";";
        } else {
            result += "target[id] = data[id];";
        }
        result += "}";
    }
    // safety else
    if(started){
        result += "else{target[id] = data[id];}";
    }
    return result;
}

void GameOfLife::Initialize() {
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
    device=all_devices[0];
    std::cout<< "Using device: "<<device.getInfo<CL_DEVICE_NAME>()<<"\n";

    std::string src = Compile();
    std::cout<<src<<std::endl;

#if __linux__
    cl::Program::Sources sources;
    sources.push_back(src);
#else
    cl::Program::Sources sources(1,std::make_pair(src.c_str(),src.length()+1));
#endif

    context = cl::Context(device);
    program = cl::Program(context,sources);

    if(program.build({device})!=CL_SUCCESS){
        std::cerr<<" Error building: "<<program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device)<<"\n";
        exit(1);
    }

    kernel = cl::Kernel(program,"ProcessMultiArray");

    const int count = rows*cols;
    // Just allocate a target matrix
    bufTarget = cl::Buffer(context, CL_MEM_READ_WRITE|CL_MEM_HOST_READ_ONLY, sizeof(int)*count);
    kernel.setArg(1, bufTarget);
    setAdditionalParameters();

}

void GameOfLife::TimeStep() {
    cl::Buffer buf(context, CL_MEM_READ_WRITE|CL_MEM_HOST_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(int)*rows*cols,data.data());

    kernel.setArg(0, buf);


    cl::CommandQueue queue(context,device);
    setRanges(queue);

    queue.enqueueReadBuffer(bufTarget,1002,0, sizeof(int)*rows*cols,data.data());

}