//
// Created by cekef on 13-Dec-18.
//

#include <array>
#include <string>
#include <map>
#include <vector>
#ifdef __APPLE__
#include <OpenCL/cl.hpp>
#elif __linux__
#include <CL/cl2.hpp>
#else
#include <CL/cl.hpp>
#endif

#ifndef OPENCLTEST_GAMEOFLIFE_H
#define OPENCLTEST_GAMEOFLIFE_H


class GameOfLife {
public:
    std::vector<std::vector<int> > getData();
    void setInitialData(const std::vector<std::vector<int> >& newData);
    std::array<std::array<int,5>,5> getWeights() const{return weights;}
    void setWeight(int row, int col, int newWeight){weights[row][col] = newWeight;}
    void addDefaultPattern(int state, int newState);
    void addDirectPattern(int state,int newState, int value);
    void addRangePattern(int state, int newState, int minRange, int maxRange);
    void addRangePatternPosInfinity(int state, int newState, int minRange);
    void addRangePatternNegInfinity(int state, int newState, int maxRange);
    void setType(std::string newType){type = std::move(newType);}
    void setSquare(){weights = {{{0,0,0,0,0},{0,1,1,1,0},{0,1,0,1,0},{0,1,1,1,0},{0,0,0,0,0}}};}
    void setCross(){weights = {{{0,0,0,0,0},{0,0,1,0,0},{0,1,0,1,0},{0,0,1,0,0},{0,0,0,0,0}}};}
    void setDiamond(){weights = {{{0,0,0,0,0},{0,1,1,1,0},{1,1,0,1,1},{0,1,1,1,0},{0,0,1,0,0}}};}
    void TimeStep();

private:
    std::string Compile() const;
    std::string generateEnding(std::string stateName) const;
    void Initialize();
    void setRanges(cl::CommandQueue& queue);
    void setAdditionalParameters();
    std::array<std::array<int,5>,5> weights = {{{{0,0,0,0,0}},{{0,1,1,1,0}},{{0,1,0,1,0}},{{0,1,1,1,0}},{{0,0,0,0,0}}}};
    std::vector<int> data;
    int rows;
    int cols;
    std::string type = "int";
    //Current state        info             new state
    std::map<int, std::map<std::vector<int>,int> > pattern;

    cl::Program program;
    cl::Context context;
    cl::Device device;
    cl::Kernel kernel;
    cl::Buffer bufTarget;

};


#endif //OPENCLTEST_GAMEOFLIFE_H
