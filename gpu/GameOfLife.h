//
// Created by cekef on 13-Dec-18.
//

#include <array>
#include <string>

#ifndef OPENCLTEST_GAMEOFLIFE_H
#define OPENCLTEST_GAMEOFLIFE_H


class GameOfLife {
public:
    std::array<std::array<int,5>,5> getWeights() const{return weights;}
    void setWeight(int row, int col, int newWeight){weights[row][col] = newWeight;}
    void setSurviveRange(const int min, const int max){minSurvive = min; maxSurvive = max;}
    void setBornRange(const int min, const int max){minBorn = min; maxBorn = max;}
    void setType(std::string newType){type = std::move(newType);}
    void setSquare(){weights = {{{0,0,0,0,0},{0,1,1,1,0},{0,1,0,1,0},{0,1,1,1,0},{0,0,0,0,0}}};}
    void setCross(){weights = {{{0,0,0,0,0},{0,0,1,0,0},{0,1,0,1,0},{0,0,1,0,0},{0,0,0,0,0}}};}
    void setDiamond(){weights = {{{0,0,0,0,0},{0,1,1,1,0},{1,1,0,1,1},{0,1,1,1,0},{0,0,1,0,0}}};}
    std::string Compile() const;


private:
    std::array<std::array<int,5>,5> weights = {{{0,0,0,0,0},{0,1,1,1,0},{0,1,0,1,0},{0,1,1,1,0},{0,0,0,0,0}}};
    std::string type = "int";
    int dimensions = 2;
    int minSurvive = 2;
    int maxSurvive = 3;
    int minBorn = 3;
    int maxBorn = 3;

};


#endif //OPENCLTEST_GAMEOFLIFE_H
