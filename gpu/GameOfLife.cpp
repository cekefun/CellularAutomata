//
// Created by cekef on 13-Dec-18.
//
#include "GameOfLife.h"
#include <iostream>
#include <fstream>
#include <vector>

std::string GameOfLife::Compile() const {
    std::ifstream programFile("../gpu/ProcessMultiArray.cl");
    std::string src(std::istreambuf_iterator<char>(programFile), (std::istreambuf_iterator<char>()));

    std::vector<std::string> parameters = {type,
                                           std::to_string(weights[2][1]),std::to_string(weights[1][1]), std::to_string(weights[3][1]),
                                           std::to_string(weights[2][3]),std::to_string(weights[1][3]),std::to_string(weights[3][3]),
                                           std::to_string(weights[1][2]),std::to_string(weights[3][2])};
    int parameter = 0;
    std::string result;

    auto last = src.begin();
    for(auto i = src.begin(); i < src.end(); i++){
        if(*i == '{' and *(i+1) == '{'){
            result.append(last,i);
            i++;
            while(*i != '}' and *(i+1) != '}'){
                i++;
            }
            i+=3;
            result.append(parameters[parameter]);
            parameter++;

            last = i;
        }
    }
    result.append(last,src.end());

    std::cout<<result<<std::endl;
    return result;
}
