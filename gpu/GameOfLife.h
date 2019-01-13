//
// Created by cekef on 13-Dec-18.
//

#include <array>
#include <string>
#include <map>
#include <vector>

#ifndef OPENCLTEST_GAMEOFLIFE_H
#define OPENCLTEST_GAMEOFLIFE_H


class GameOfLife {
public:
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
    std::string Compile() const;


private:
    std::string generateEnding(std::string stateName) const;
    std::array<std::array<int,5>,5> weights = {{{{0,0,0,0,0}},{{0,1,1,1,0}},{{0,1,0,1,0}},{{0,1,1,1,0}},{{0,0,0,0,0}}}};
    std::string type = "int";
    int dimensions = 2;
    //Current state        info             new state
    std::map<int, std::map<std::vector<int>,int> > pattern;

};


#endif //OPENCLTEST_GAMEOFLIFE_H
