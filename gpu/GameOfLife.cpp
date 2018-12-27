//
// Created by cekef on 13-Dec-18.
//
#include "GameOfLife.h"
#include <iostream>
#include <fstream>
#include <vector>

std::string GameOfLife::Compile() const {


    std::string result = "typedef "+type+" myType;\n";
#ifdef NAIVE
    // This is the most naive way
    result += "void kernel ProcessMultiArray(global myType* data, global myType* target){\n"
              "    size_t id = get_global_id(0)";

    if(dimensions > 1){
        result += "+ get_global_id(1) * get_global_size(0)";
    }
    if(dimensions > 2){
        result += "+ get_global_id(2)*get_global_size(0)*get_global_size(1)";
    }
    result +=";\n"
              "    myType neighbours = 0;";

    if(weights[2][1]!= 0 && weights[1][1]!=0 && weights[3][1]!=0 && dimensions > 1){
        result += "if(get_global_id(0) !=0){\n";
        if(weights[1][2] != 0)
        {
            //2D Left
            result +="      neighbours +=";
            if(weights[2][1]!= 1)
            {
                result += std::to_string(weights[2][1])+"*";
            }

            result += "(data[(get_global_id(0)-1) + get_global_id(1) * get_global_size(0)]);\n";

        }
        if(weights[1][1] != 0)
        {
            //2D TopLeft
            result += "        if (get_global_id(1) != 0){\n"
                      "            neighbours += ";
            if(weights[1][1] != 0) {
                result += std::to_string(weights[1][1]) + "*";
            }
            result += "(data[(get_global_id(0)-1) + (get_global_id(1)-1) * get_global_size(0)]);\n"

                      "        }\n";
        }
        if(weights[3][1]!= 0)
        {
            //2D BotLeft
            result +=  "        if (get_global_id(1) != get_global_size(1)-1){\n"
                       "            neighbours += ";
            if(weights[3][1]!= 1){
                result+=std::to_string(weights[3][1])+"*";
            }
            result += "(data[(get_global_id(0)-1)+(get_global_id(1)+1) * get_global_size(0)]);\n"
                       "        }\n";
        }
        result += "    }";
    }

    if(weights[2][3]!= 0 && weights[1][3]!=0 && weights[3][3]!=0 && dimensions > 1){
        result += "if(get_global_id(0) != get_global_size(0)-1){\n";
        if(weights[2][3] != 0)
        {
            //2D Right
            result += "neighbours += ";
            if(weights[2][3] != 1){
                result+=std::to_string(weights[2][3])+"*";
            }
            result += "(data[(get_global_id(0)+1) + get_global_id(1) * get_global_size(0)]);";

        }
        if(weights[1][3] != 0)
        {
            //2D TopRight
            result += "        if (get_global_id(1) != 0){\n"
                      "            neighbours += ";
            if(weights[1][3]){
                result +=std::to_string(weights[1][3]) + "*";
            }
            result += "(data[(get_global_id(0)+1) +(get_global_id(1)-1) * get_global_size(0)]);\n"
                                                                                    "        }\n";
        }
        if(weights[3][3]!= 0)
        {
            // 2D BotRight
            result +=  "        if (get_global_id(1) != get_global_size(1)-1){\n"
                       "            neighbours += ";
            if(weights[3][3]){
                result += std::to_string(weights[3][3])+"*";
            }
            result += "(data[(get_global_id(0)+1)+(get_global_id(1)+1) * get_global_size(0)]);\n"
                                                                                  "        }\n";
        }
        result += "    }";
    }

    if (weights[1][2] != 0){
        // Top
        result += "if(get_global_id(1) != 0){\n"
                  "        neighbours += ";
        if(weights[1][2]!= 1){
            result += std::to_string(weights[1][2]) +"*";
        }
        result += "(data[get_global_id(0)+(get_global_id(1)-1) * get_global_size(0)]);\n"
                  "    }";
    }
    if (weights[3][2] != 0){
        //Bot
        result += "if(get_global_id(1) != get_global_size(1)-1){\n"
                  "        neighbours += ";
        if(weights[3][2] != 1){
            result += std::to_string(weights[3][2])+"*";
        }
        result += "(data[get_global_id(0) + (get_global_id(1)+1) * get_global_size(0)]);\n"
                  "    }";

    }


    result += "myType state = data[id];\n"
              "\n"
              "    if(state == 1 && neighbours < 2){\n"
              "        target[id] = 0;\n"
              "    }\n"
              "    if(state == 1 && neighbours > 3){\n"
              "        target[id] = 0;\n"
              "    }\n"
              "    if(state == 1 && neighbours >=2 && neighbours <= 3){\n"
              "        target[id] = 1;\n"
              "    }\n"
              "    if(state == 0 && neighbours == 3){\n"
              "        target[id] = 1;\n"
              "    }"
              "}";
#endif
#ifdef BY_ROW
    result += "void kernel ProcessMultiArray(global myType* data, global myType* target, int length){\n"
              "    myType nextLeft = 0;\n"
              "    myType nextSelf = data[(get_global_id(0)) * length];\n";
    if(dimensions >1){
        result += "    myType nextTopLeft = 0;\n"
                  "    myType nextBotLeft = 0;\n"
                  "    myType nextTop = 0;\n"
                  "    if (get_global_id(0)!= 0){\n"
                  "        nextTop = data[(get_global_id(0)-1) * length];\n"
                  "    }\n"

                  "    myType nextBot = 0;\n"
                  "    if (get_global_id(0)!= get_global_size(0)-1){\n"
                  "        nextBot = data[(get_global_id(0)+1) * length];\n"
                  "    }\n";
    }
    result += "    myType neighbours = 0;\n"
              "    size_t id;\n"
              "    for(int i = 0; i < length - 1; i++){\n"
              "        id = get_global_id(0) * length + i;\n"
              "        neighbours = "  + std::to_string(weights[1][1]) + "* nextTopLeft + "
                                        + std::to_string(weights[2][1])+"* nextLeft + "
                                        + std::to_string(weights[3][1])+"* nextBotLeft + "
                                        + std::to_string(weights[1][2])+"* nextTop + "
                                        + std::to_string(weights[3][1])+"* nextBot;\n"
              "        nextTopLeft = nextTop;\n"
              "        nextLeft = nextSelf;\n"
              "        nextBotLeft = nextBot;\n"
              "        myType self = nextSelf;\n"
              "        nextSelf = data[(get_global_id(0)) * length + i+1];\n"
              "        neighbours += "+std::to_string(weights[2][3])+"* nextSelf;\n"
              "        if (get_global_id(0)!= 0){\n"
              "            nextTop = data[(get_global_id(0)-1) * length + i+1];\n"
              "            neighbours += "+std::to_string(weights[1][3])+"* nextTop;\n"
              "        }\n"
              "        if(get_global_id(0) != get_global_size(0)-1){\n"
              "            nextBot = data[(get_global_id(0)+1) * length + i+1];\n"
              "            neighbours += "+std::to_string(weights[3][3])+"* nextBot;\n"
              "        }\n"
              "\n"
              "        if(self == 1 && neighbours < 2){\n"
              "            target[id] = 0;\n"
              "        }\n"
              "        if(self == 1 && neighbours > 3){\n"
              "            target[id] = 0;\n"
              "        }\n"
              "        if(self == 1 && neighbours >=2 && neighbours <= 3){\n"
              "            target[id] = 1;\n"
              "        }\n"
              "        if(self == 0 && neighbours == 3){\n"
              "            target[id] = 1;\n"
              "        }\n"
              "    }\n"
              "    neighbours = "  + std::to_string(weights[1][1]) + "* nextTopLeft + "
                                    + std::to_string(weights[2][1])+"* nextLeft + "
                                    + std::to_string(weights[3][1])+"* nextBotLeft + "
                                    + std::to_string(weights[1][2])+"* nextTop + "
                                    + std::to_string(weights[3][1])+"* nextBot;\n"
              "    id = get_global_id(0) * length + length -1;\n"
              "    if(nextSelf == 1 && neighbours < 2){\n"
              "        target[id] = 0;\n"
              "    }\n"
              "    if(nextSelf == 1 && neighbours > 3){\n"
              "        target[id] = 0;\n"
              "    }\n"
              "    if(nextSelf == 1 && neighbours >=2 && neighbours <= 3){\n"
              "        target[id] = 1;\n"
              "    }\n"
              "    if(nextSelf == 0 && neighbours == 3){\n"
              "        target[id] = 1;\n"
              "    }\n"
              "\n"
              "}";
#endif


    /*
     *
     * void kernel ProcessMultiArray(global myType* data, global myType* target){
    size_t id = (get_global_id(1) * get_global_size(0)) + get_global_id(0);

    myType neighbours = 0;

     *
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
     */
    return result;

}
