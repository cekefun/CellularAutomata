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


    if(weights[0][0] != 0 && weights[1][0]!= 0 && weights[2][0] != 0 && weights[3][0] != 0 && weights[4][0] != 0){
        result += "if(get_global_id(0) > 1){\n";
        if(weights[0][0] != 0){
            result += "if(get_global_id(1)>1){\n"
                      "neighbours += ";
            if(weights[0][0]!= 1){
                result += std::to_string(weights[0][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)-2) * get_global_size(0)]);}";
        }
        if(weights[1][0] != 0){
            result += "if(get_global_id(1)>0){\n"
                      "neighbours += ";
            if(weights[1][0]!= 1){
                result += std::to_string(weights[1][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)-1) * get_global_size(0)]);}";
        }
        if(weights[2][0] != 0){
            result += "neighbours += ";
            if(weights[2][0]!= 1){
                result += std::to_string(weights[2][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)) * get_global_size(0)]);";
        }
        if(weights[3][0]!= 0){
            result += "if(get_global_id(1)<get_global_size(1)-1){\n"
                      "neighbours += ";
            if(weights[3][0]!= 1){
                result += std::to_string(weights[3][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)+1) * get_global_size(0)]);}";
        }
        if(weights[4][0]!= 0){
            result += "if(get_global_id(1)<get_global_size(1)-2){\n"
                      "neighbours += ";
            if(weights[4][0]!= 1){
                result += std::to_string(weights[4][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)+2) * get_global_size(0)]);}";
        }
        result += "}\n";
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

    if(weights[0][4] != 0 && weights[1][4]!= 0 && weights[2][4] != 0 && weights[3][4] != 0 && weights[4][4] != 0){
        result += "if(get_global_id(0) < get_global_size(0)-2){\n";
        if(weights[0][4] != 0){
            result += "if(get_global_id(1)>1){\n"
                      "neighbours += ";
            if(weights[0][4]!= 1){
                result += std::to_string(weights[0][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)-2) * get_global_size(0)]);}";
        }
        if(weights[1][4] != 0){
            result += "if(get_global_id(1)>0){\n"
                      "neighbours += ";
            if(weights[1][4]!= 1){
                result += std::to_string(weights[1][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)-1) * get_global_size(0)]);}";
        }
        if(weights[2][4] != 0){
            result += "neighbours += ";
            if(weights[2][4]!= 1){
                result += std::to_string(weights[2][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)) * get_global_size(0)]);";
        }
        if(weights[3][4]!= 0){
            result += "if(get_global_id(1)<get_global_size(1)-1){\n"
                      "neighbours += ";
            if(weights[3][4]!= 1){
                result += std::to_string(weights[3][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)+1) * get_global_size(0)]);}";
        }
        if(weights[4][4]!= 0){
            result += "if(get_global_id(1)<get_global_size(1)-2){\n"
                      "neighbours += ";
            if(weights[4][4]!= 1){
                result += std::to_string(weights[4][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)+2) * get_global_size(0)]);}";
        }
        result += "}\n";
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

    if(weights[0][1]!=0 && weights[0][2] != 0 && weights[0][3] != 0){
        result += "if(get_global_id(1) > 1){";
        if(weights[0][1]!= 0){
            result += "if(get_global_id(0)> 0){"
                      "neighbours +=";
            if(weights[0][1] != 1){
                result += std::to_string(weights[0][1]) + "* ";
            }
            result += "(data[(get_global_id(0)-1)+(get_global_id(1)-2) * get_global_size(0)]);}";
        }
        if(weights[0][2] != 0){
            result +="neighbours +=";
            if(weights[0][2] != 1){
                result += std::to_string(weights[0][2]) + "* ";
            }
            result += "(data[(get_global_id(0))+(get_global_id(1)-2) * get_global_size(0)]);";
        }
        if(weights[0][3]!= 0){
            result += "if(get_global_id(0)< get_global_size(0)-1){"
                      "neighbours +=";
            if(weights[0][3] != 1){
                result += std::to_string(weights[0][3]) + "* ";
            }
            result += "(data[(get_global_id(0)+1)+(get_global_id(1)-2) * get_global_size(0)]);}";
        }
        result += "}";
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

    if(weights[4][1]!=0 && weights[4][2] != 0 && weights[4][3] != 0){
        result += "if(get_global_id(1) < get_global_size(1)-2){";
        if(weights[4][1]!= 0){
            result += "if(get_global_id(0)> 0){"
                      "neighbours +=";
            if(weights[4][1] != 1){
                result += std::to_string(weights[4][1]) + "* ";
            }
            result += "(data[(get_global_id(0)-1)+(get_global_id(1)+2) * get_global_size(0)]);}";
        }
        if(weights[4][2] != 0){
            result +="neighbours +=";
            if(weights[4][2] != 1){
                result += std::to_string(weights[4][2]) + "* ";
            }
            result += "(data[(get_global_id(0))+(get_global_id(1)+2) * get_global_size(0)]);";
        }
        if(weights[4][3]!= 0){
            result += "if(get_global_id(0)< get_global_size(0)-1){"
                      "neighbours +=";
            if(weights[4][3] != 1){
                result += std::to_string(weights[4][3]) + "* ";
            }
            result += "(data[(get_global_id(0)+1)+(get_global_id(1)+2) * get_global_size(0)]);}";
        }
        result += "}";
    }

    result += "myType state = data[id];\n"
              "\n";
    result += "    if(state == 1 && (neighbours < "+std::to_string(minSurvive)+" || neighbours >"+std::to_string(maxSurvive)+")){\n"
              "        target[id] = 0;\n"
              "    }\n"

              "    else if(state == 0 && neighbours >= "+std::to_string(minBorn)+" && neighbours <= "+std::to_string(maxBorn)+"){\n"
              "        target[id] = 1;\n"
              "    } else{target[id] = data[id];}"
              "}";
#endif
#ifdef BY_ROW
    result += "void kernel ProcessMultiArray(global myType* data, global myType* target, int length){\n";
    if(weights[0][0]!= 0){
        result += "    myType nextTopTopLeftLeft = 0;\n";
    }
    if(weights[1][0]!= 0){
        result += "    myType nextTopLeftLeft = 0;\n";
    }
    if(weights[2][0] != 0){
        result += "    myType nextLeftLeft = 0;\n";
    }
    if(weights[3][0] != 0){
        result += "    myType nextBotLeftLeft = 0;\n";
    }
    if(weights[4][0] != 0){
        result += "    myType nextBotBotLeftLeft = 0;\n";
    }

    if(weights[0][0]!= 0 || weights[0][1] != 0){
        result += "    myType nextTopTopLeft = 0;\n";
    }
    if(weights[1][0]!= 0 || weights[1][1] != 0) {
        result += "    myType nextTopLeft = 0;\n";
    }
    if(weights[2][0]!= 0 || weights[2][1] != 0) {
        result += "    myType nextLeft = 0;\n";
    }
    if(weights[3][0]!= 0 || weights[3][1] != 0) {
        result += "    myType nextBotLeft = 0;\n";
    }
    if(weights[4][0]!= 0 || weights[4][1] != 0) {
        result += "    myType nextBotBotLeft = 0;\n";
    }

    if(weights[0][0]!= 0 || weights[0][1] != 0 || weights[0][2] != 0){
        result += "    myType nextTopTop = 0;\n"
                  "    if (get_global_id(0)>1){\n"
                  "        nextTopTop = data[(get_global_id(0)-2) * length];\n"
                  "}\n";
    }
    if(weights[1][0]!= 0 || weights[1][1] != 0 || weights[1][2] != 0) {
        result += "    myType nextTop = 0;\n"
                  "    if (get_global_id(0)!= 0){\n"
                  "        nextTop = data[(get_global_id(0)-1) * length];\n"
                  "    }\n";
    }
    //Starting here, the middle row is required
    result += "    myType nextSelf = 0;\n"
              "    nextSelf = data[(get_global_id(0)) * length];\n";

    if(weights[3][0]!= 0 || weights[3][1] != 0 || weights[3][2] != 0) {
        result += "    myType nextBot = 0;\n"
                  "    if (get_global_id(0)!= get_global_size(0)-1){\n"
                  "        nextBot = data[(get_global_id(0)+1) * length];\n"
                  "    }\n";
    }
    if(weights[4][0]!= 0 || weights[4][1] != 0 || weights[4][2] != 0) {
        result += "    myType nextBotBot = 0;\n"
                  "    if (get_global_id(0)< get_global_size(0)-2){\n"
                  "        nextBotBot = data[(get_global_id(0)+2) * length];\n"
                  "    }\n";
    }                                                                                       //Needs to exist for lookahead
    if(weights[0][0]!= 0 || weights[0][1] != 0 || weights[0][2] != 0 || weights[0][3] != 0 || weights[0][4] != 0){
        result += "    myType nextTopTopRight = 0;\n"
                  "    if (get_global_id(0)>1){\n"
                  "        nextTopTopRight = data[(get_global_id(0)-2) * length + 1];\n"
                  "}\n";
    }
    if(weights[1][0]!= 0 || weights[1][1] != 0 || weights[1][2] != 0 || weights[1][3] != 0 || weights[1][4] != 0) {
        result += "    myType nextTopRight = 0;\n"
                  "    if (get_global_id(0)!= 0){\n"
                  "        nextTopRight = data[(get_global_id(0)-1) * length + 1];\n"
                  "    }\n";
    }
    //Starting here, the middle row is required
    result += "    myType nextRight = 0;\n"
              "    nextRight = data[(get_global_id(0)) * length + 1];\n";

    if(weights[3][0]!= 0 || weights[3][1] != 0 || weights[3][2] != 0 || weights[3][3] != 0 || weights[3][4] != 0) {
        result += "    myType nextBotRight = 0;\n"
                  "    if (get_global_id(0)!= get_global_size(0)-1){\n"
                  "        nextBotRight = data[(get_global_id(0)+1) * length + 1];\n"
                  "    }\n";
    }
    if(weights[4][0]!= 0 || weights[4][1] != 0 || weights[4][2] != 0 || weights[4][3] != 0 || weights[4][4] != 0) {
        result += "    myType nextBotBotRight = 0;\n"
                  "    if (get_global_id(0)< get_global_size(0)-2){\n"
                  "        nextBotBotRight = data[(get_global_id(0)+2) * length + 1];\n"
                  "    }\n";
    }


    result += "    myType neighbours = 0;\n"
              "    size_t id;\n"
              "    for(int i = 0; i < length - 2; i++){\n"
              "        id = get_global_id(0) * length + i;\n"
              "        neighbours = ";

    if(weights[0][0] != 0|| weights[0][1] != 0 || weights[0][2]!= 0 || weights[0][3]!=0 ||
    weights[1][0] != 0|| weights[1][1] != 0 || weights[1][2]!= 0 || weights[1][3]!=0 ||
    weights[2][0] != 0|| weights[2][1] != 0 || weights[2][3]!=0 ||
    weights[3][0] != 0|| weights[3][1] != 0 || weights[3][2]!= 0 || weights[3][3]!=0||
    weights[4][0] != 0|| weights[4][1] != 0 || weights[4][2]!= 0 || weights[4][3]!=0) {
        if (weights[0][0] != 0) {
            if (weights[0][0] != 1) {
                result += std::to_string(weights[0][0]) + "*";
            }
            result += " nextTopTopLeftLeft +";
        }
        if (weights[0][1] != 0) {
            if (weights[0][1] != 1) {
                result += std::to_string(weights[0][1]) + "*";
            }
            result += " nextTopTopLeft +";
        }
        if (weights[0][2] != 0) {
            if (weights[0][2] != 1) {
                result += std::to_string(weights[0][2]) + "*";
            }
            result += " nextTopTop +";
        }
        if (weights[0][3] != 0) {
            if (weights[0][3] != 1) {
                result += std::to_string(weights[0][3]) + "*";
            }
            result += " nextTopTopRight +";
        }
        if (weights[1][0] != 0) {
            if (weights[1][0] != 1) {
                result += std::to_string(weights[1][0]) + "*";
            }
            result += " nextTopLeftLeft +";
        }
        if (weights[1][1] != 0) {
            if (weights[1][1] != 1) {
                result += std::to_string(weights[1][1]) + "*";
            }
            result += " nextTopLeft +";
        }
        if (weights[1][2] != 0) {
            if (weights[1][2] != 1) {
                result += std::to_string(weights[1][2]) + "*";
            }
            result += " nextTop +";
        }
        if (weights[1][3] != 0) {
            if (weights[1][3] != 1) {
                result += std::to_string(weights[1][3]) + "*";
            }
            result += " nextTopRight +";
        }
        if (weights[2][0] != 0) {
            if (weights[2][0] != 1) {
                result += std::to_string(weights[2][0]) + "*";
            }
            result += " nextLeftLeft +";
        }
        if (weights[2][1] != 0) {
            if (weights[2][1] != 1) {
                result += std::to_string(weights[2][1]) + "*";
            }
            result += " nextLeft +";
        }
        if (weights[2][3] != 0) {
            if (weights[2][3] != 1) {
                result += std::to_string(weights[2][3]) + "*";
            }
            result += " nextRight +";
        }
        if (weights[3][0] != 0) {
            if (weights[3][0] != 1) {
                result += std::to_string(weights[3][0]) + "*";
            }
            result += " nextBotLeftLeft +";
        }
        if (weights[3][1] != 0) {
            if (weights[3][1] != 1) {
                result += std::to_string(weights[3][1]) + "*";
            }
            result += " nextBotLeft +";
        }
        if (weights[3][2] != 0) {
            if (weights[3][2] != 1) {
                result += std::to_string(weights[3][2]) + "*";
            }
            result += " nextBot +";
        }
        if (weights[3][3] != 0) {
            if (weights[3][3] != 1) {
                result += std::to_string(weights[3][3]) + "*";
            }
            result += " nextBotRight +";
        }
        if (weights[4][0] != 0) {
            if (weights[4][0] != 1) {
                result += std::to_string(weights[4][0]) + "*";
            }
            result += " nextBotBotLeftLeft +";
        }
        if (weights[4][1] != 0) {
            if (weights[4][1] != 1) {
                result += std::to_string(weights[4][1]) + "*";
            }
            result += " nextBotBotLeft +";
        }
        if (weights[4][2] != 0) {
            if (weights[4][2] != 1) {
                result += std::to_string(weights[4][2]) + "*";
            }
            result += " nextBotBot +";
        }
        if (weights[4][3] != 0) {
            if (weights[4][3] != 1) {
                result += std::to_string(weights[4][3]) + "*";
            }
            result += " nextBotBotRight +";
        }
        result.pop_back();
        result += ";";
    } else{
        result += "0;";
    }
    if(weights[0][0] != 0){
        result += "        nextTopTopLeftLeft = nextTopTopLeft;";
    }if(weights[0][0] != 0 || weights[0][1] != 0){
        result += "        nextTopTopLeft = nextTopTop;";
    }if(weights[0][0] != 0 || weights[0][1] != 0 || weights[0][2] != 0){
        result+= "        nextTopTop = nextTopTopRight;";
    }
    if(weights[1][0] != 0){
        result += "        nextTopLeftLeft = nextTopLeft;";
    }if(weights[1][0] != 0 || weights[1][1] != 0){
        result += "        nextTopLeft = nextTop;";
    }if(weights[1][0] != 0 || weights[1][1] != 0 || weights[1][2] != 0){
        result+= "        nextTop = nextTopRight;";
    }
    if(weights[2][0] != 0){
        result += "        nextLeftLeft = nextLeft;";
    }if(weights[2][0] != 0 || weights[2][1] != 0) {
        result += "        nextLeft = nextSelf;";
    }
    result += "        myType self = nextSelf;";
    result+= "        nextSelf = nextRight;";
    if(weights[3][0] != 0){
        result += "        nextBotLeftLeft = nextBotLeft;";
    }if(weights[3][0] != 0 || weights[3][1] != 0){
        result += "        nextBotLeft = nextBot;";
    }if(weights[3][0] != 0 || weights[3][1] != 0 || weights[3][2] != 0){
        result+= "        nextBot = nextBotRight;";
    }
    if(weights[4][0] != 0){
        result += "        nextBotBotLeftLeft = nextBotBotLeft;";
    }if(weights[4][0] != 0 || weights[4][1] != 0){
        result += "        nextBotBotLeft = nextBotBot;";
    }if(weights[4][0] != 0 || weights[4][1] != 0 || weights[4][2] != 0){
        result+= "        nextBotBot = nextBotBotRight;";
    }

    result += "        nextRight = data[(get_global_id(0)) * length + i + 2];\n";
    if(weights[2][4] != 0){
        result += "        neighbours += ";
        if(weights[2][4] != 1){
            result += std::to_string(weights[2][4])+"*";
        }
        result += " nextRight;\n";
    }
    if(weights[0][0]!= 0 || weights[0][1] != 0 || weights[0][2] != 0 || weights[0][3] != 0 || weights[0][4] != 0) {
        result += "if (get_global_id(0) < 1){"
                  "        nextTopTopRight = data[(get_global_id(0)-2) * length + i+2]";
        if (weights[0][4] != 0) {
            result += "neighbours += ";
            if (weights[0][4] != 1) {
                result += std::to_string(weights[0][4]) + "*";
            }
            result += " nextTopTopRight;\n";
        }
    }
    if(weights[1][0]!= 0 || weights[1][1] != 0 || weights[1][2] != 0 || weights[1][3] != 0 || weights[1][4] != 0) {
        result += "        if (get_global_id(0)!= 0){\n"
                  "            nextTopRight = data[(get_global_id(0)-1) * length + i+2];\n";
        if (weights[1][4] != 0) {
            result += "neighbours += ";
            if (weights[1][4] != 1) {
                result += std::to_string(weights[1][4]) + "*";
            }
            result += " nextTopRight;\n";
        }
    }
    if(weights[3][0]!= 0 || weights[3][1] != 0 || weights[3][2] != 0 || weights[3][3] != 0 || weights[3][4] != 0) {
        result += "        }\n"
                  "        if(get_global_id(0) != get_global_size(0)-1){\n"
                  "            nextBotRight = data[(get_global_id(0)+1) * length + i+2];\n";

        if (weights[3][4] != 0) {
            result += "neighbours += ";
            if (weights[3][4] != 1) {
                result += std::to_string(weights[3][4]) + "*";
            }
            result += " nextBotRight;\n";
        }
    }
    if(weights[4][0]!= 0 || weights[4][1] != 0 || weights[4][2] != 0 || weights[4][3] != 0 || weights[4][4] != 0) {
        result += "        }\n"
                  "        if(get_global_id(0) < get_global_size(0)-2){\n"
                  "            nextBotBotRight = data[(get_global_id(0)+2) * length + i+2];\n";

        if (weights[4][4] != 0) {
            result += "neighbours += ";
            if (weights[4][4] != 1) {
                result += std::to_string(weights[4][4]) + "*";
            }
            result += " nextBotBotRight;\n";
        }
    }

    result += "        }\n";
    result += "    if(self == 1 && (neighbours < "+std::to_string(minSurvive)+" || neighbours >"+std::to_string(maxSurvive)+")){\n"
              "        target[id] = 0;\n"
              "    }\n"
              "    else if(self == 0 && neighbours >= "+std::to_string(minBorn)+" && neighbours <= "+std::to_string(maxBorn)+"){\n"
              "        target[id] = 1;\n"
              "    } else{target[id] = data[id];}";
    result += "    }\n"
              "    neighbours = ";

    if(weights[0][0] != 0|| weights[0][1] != 0 || weights[0][2]!= 0 || weights[0][3]!=0 ||
       weights[1][0] != 0|| weights[1][1] != 0 || weights[1][2]!= 0 || weights[1][3]!=0 ||
       weights[2][0] != 0|| weights[2][1] != 0 || weights[2][3]!=0 ||
       weights[3][0] != 0|| weights[3][1] != 0 || weights[3][2]!= 0 || weights[3][3]!=0||
       weights[4][0] != 0|| weights[4][1] != 0 || weights[4][2]!= 0 || weights[4][3]!=0) {
        if (weights[0][0] != 0) {
            if (weights[0][0] != 1) {
                result += std::to_string(weights[0][0]) + "*";
            }
            result += " nextTopTopLeftLeft +";
        }
        if (weights[0][1] != 0) {
            if (weights[0][1] != 1) {
                result += std::to_string(weights[0][1]) + "*";
            }
            result += " nextTopTopLeft +";
        }
        if (weights[0][2] != 0) {
            if (weights[0][2] != 1) {
                result += std::to_string(weights[0][2]) + "*";
            }
            result += " nextTopTop +";
        }
        if (weights[0][3] != 0) {
            if (weights[0][3] != 1) {
                result += std::to_string(weights[0][3]) + "*";
            }
            result += " nextTopTopRight +";
        }
        if (weights[1][0] != 0) {
            if (weights[1][0] != 1) {
                result += std::to_string(weights[1][0]) + "*";
            }
            result += " nextTopLeftLeft +";
        }
        if (weights[1][1] != 0) {
            if (weights[1][1] != 1) {
                result += std::to_string(weights[1][1]) + "*";
            }
            result += " nextTopLeft +";
        }
        if (weights[1][2] != 0) {
            if (weights[1][2] != 1) {
                result += std::to_string(weights[1][2]) + "*";
            }
            result += " nextTop +";
        }
        if (weights[1][3] != 0) {
            if (weights[1][3] != 1) {
                result += std::to_string(weights[1][3]) + "*";
            }
            result += " nextTopRight +";
        }
        if (weights[2][0] != 0) {
            if (weights[2][0] != 1) {
                result += std::to_string(weights[2][0]) + "*";
            }
            result += " nextLeftLeft +";
        }
        if (weights[2][1] != 0) {
            if (weights[2][1] != 1) {
                result += std::to_string(weights[2][1]) + "*";
            }
            result += " nextLeft +";
        }
        if (weights[2][3] != 0) {
            if (weights[2][3] != 1) {
                result += std::to_string(weights[2][3]) + "*";
            }
            result += " nextRight +";
        }
        if (weights[3][0] != 0) {
            if (weights[3][0] != 1) {
                result += std::to_string(weights[3][0]) + "*";
            }
            result += " nextBotLeftLeft +";
        }
        if (weights[3][1] != 0) {
            if (weights[3][1] != 1) {
                result += std::to_string(weights[3][1]) + "*";
            }
            result += " nextBotLeft +";
        }
        if (weights[3][2] != 0) {
            if (weights[3][2] != 1) {
                result += std::to_string(weights[3][2]) + "*";
            }
            result += " nextBot +";
        }
        if (weights[3][3] != 0) {
            if (weights[3][3] != 1) {
                result += std::to_string(weights[3][3]) + "*";
            }
            result += " nextBotRight +";
        }
        if (weights[4][0] != 0) {
            if (weights[4][0] != 1) {
                result += std::to_string(weights[4][0]) + "*";
            }
            result += " nextBotBotLeftLeft +";
        }
        if (weights[4][1] != 0) {
            if (weights[4][1] != 1) {
                result += std::to_string(weights[4][1]) + "*";
            }
            result += " nextBotBotLeft +";
        }
        if (weights[4][2] != 0) {
            if (weights[4][2] != 1) {
                result += std::to_string(weights[4][2]) + "*";
            }
            result += " nextBotBot +";
        }
        if (weights[4][3] != 0) {
            if (weights[4][3] != 1) {
                result += std::to_string(weights[4][3]) + "*";
            }
            result += " nextBotBotRight +";
        }
        result.pop_back();
        result += ";";
    } else{
        result += "0;";
    }
    result +="    id = get_global_id(0) * length + length -2;\n";
    result +=  "    if(nextSelf == 1 && (neighbours < "+std::to_string(minSurvive)+" || neighbours >"+std::to_string(maxSurvive)+")){\n"
               "        target[id] = 0;\n"
               "    }\n"
               "    else if(nextSelf == 0 && neighbours >= "+std::to_string(minBorn)+" && neighbours <= "+std::to_string(maxBorn)+"){\n"
               "        target[id] = 1;\n"
               "    } else{target[id] = data[id];}";
    result += "    neighbours = ";

    if(weights[0][0] != 0|| weights[0][1] != 0 || weights[0][2]!= 0 ||
       weights[1][0] != 0|| weights[1][1] != 0 || weights[1][2]!= 0 ||
       weights[2][0] != 0|| weights[2][1] != 0 ||
       weights[3][0] != 0|| weights[3][1] != 0 || weights[3][2]!= 0||
       weights[4][0] != 0|| weights[4][1] != 0 || weights[4][2]!= 0) {
        if (weights[0][0] != 0) {
            if (weights[0][0] != 1) {
                result += std::to_string(weights[0][0]) + "*";
            }
            result += " nextTopTopLeft +";
        }
        if (weights[0][1] != 0) {
            if (weights[0][1] != 1) {
                result += std::to_string(weights[0][1]) + "*";
            }
            result += " nextTopTop +";
        }
        if (weights[0][2] != 0) {
            if (weights[0][2] != 1) {
                result += std::to_string(weights[0][2]) + "*";
            }
            result += " nextTopTopRight +";
        }

        if (weights[1][0] != 0) {
            if (weights[1][0] != 1) {
                result += std::to_string(weights[1][0]) + "*";
            }
            result += " nextTopLeft +";
        }
        if (weights[1][1] != 0) {
            if (weights[1][1] != 1) {
                result += std::to_string(weights[1][1]) + "*";
            }
            result += " nextTop +";
        }
        if (weights[1][2] != 0) {
            if (weights[1][2] != 1) {
                result += std::to_string(weights[1][2]) + "*";
            }
            result += " nextTopRight +";
        }
        if (weights[2][0] != 0) {
            if (weights[2][0] != 1) {
                result += std::to_string(weights[2][0]) + "*";
            }
            result += " nextLeft +";
        }
        if (weights[2][1] != 0) {
            if (weights[2][1] != 1) {
                result += std::to_string(weights[2][1]) + "*";
            }
            result += " nextSelf +";
        }
        if (weights[3][0] != 0) {
            if (weights[3][0] != 1) {
                result += std::to_string(weights[3][0]) + "*";
            }
            result += " nextBotLeft +";
        }
        if (weights[3][1] != 0) {
            if (weights[3][1] != 1) {
                result += std::to_string(weights[3][1]) + "*";
            }
            result += " nextBot +";
        }
        if (weights[3][2] != 0) {
            if (weights[3][2] != 1) {
                result += std::to_string(weights[3][2]) + "*";
            }
            result += " nextBotRight +";
        }
        if (weights[4][0] != 0) {
            if (weights[4][0] != 1) {
                result += std::to_string(weights[4][0]) + "*";
            }
            result += " nextBotBotLeft +";
        }
        if (weights[4][1] != 0) {
            if (weights[4][1] != 1) {
                result += std::to_string(weights[4][1]) + "*";
            }
            result += " nextBotBot +";
        }
        if (weights[4][2] != 0) {
            if (weights[4][2] != 1) {
                result += std::to_string(weights[4][2]) + "*";
            }
            result += " nextBotBotRight +";
        }
        result.pop_back();
        result += ";";
    } else{
        result += "0;";
    }
    result +="    id = get_global_id(0) * length + length -1;\n"
             "    if(nextRight == 1 && (neighbours < "+std::to_string(minSurvive)+" || neighbours >"+std::to_string(maxSurvive)+")){\n"
             "        target[id] = 0;\n"
             "    }\n"
             "    else if(nextRight == 0 && neighbours >= "+std::to_string(minBorn)+" && neighbours <= "+std::to_string(maxBorn)+"){\n"
             "        target[id] = 1;\n"
             "    } else{target[id] = data[id];}"
      "}";
#endif
    return result;

}
