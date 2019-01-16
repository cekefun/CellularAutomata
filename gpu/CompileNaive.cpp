//
// Created by cekef on 16-Jan-19.
//
#include "GameOfLife.h"

void GameOfLife::setAdditionalParameters() {
}

void GameOfLife::setRanges(cl::CommandQueue& queue) {
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(rows, cols));
}

std::string GameOfLife::Compile() const {
    std::string result = "typedef " + type + " myType;\n";
    // This is the most naive way
    result += "void kernel ProcessMultiArray(global myType* data, global myType* target){\n"
              "    size_t id = get_global_id(0)+ get_global_id(1) * get_global_size(0);"
              "    myType neighbours = 0;";

    if (weights[2][1] != 0 && weights[1][1] != 0 && weights[3][1] != 0) {
        result += "if(get_global_id(0) !=0){\n";
        if (weights[1][2] != 0) {
            //2D Left
            result += "      neighbours +=";
            if (weights[2][1] != 1) {
                result += std::to_string(weights[2][1]) + "*";
            }

            result += "(data[(get_global_id(0)-1) + get_global_id(1) * get_global_size(0)]);\n";

        }
        if (weights[1][1] != 0) {
            //2D TopLeft
            result += "        if (get_global_id(1) != 0){\n"
                      "            neighbours += ";
            if (weights[1][1] != 0) {
                result += std::to_string(weights[1][1]) + "*";
            }
            result += "(data[(get_global_id(0)-1) + (get_global_id(1)-1) * get_global_size(0)]);\n"

                      "        }\n";
        }
        if (weights[3][1] != 0) {
            //2D BotLeft
            result += "        if (get_global_id(1) != get_global_size(1)-1){\n"
                      "            neighbours += ";
            if (weights[3][1] != 1) {
                result += std::to_string(weights[3][1]) + "*";
            }
            result += "(data[(get_global_id(0)-1)+(get_global_id(1)+1) * get_global_size(0)]);\n"
                      "        }\n";
        }
        result += "    }";
    }


    if (weights[0][0] != 0 && weights[1][0] != 0 && weights[2][0] != 0 && weights[3][0] != 0 && weights[4][0] != 0) {
        result += "if(get_global_id(0) > 1){\n";
        if (weights[0][0] != 0) {
            result += "if(get_global_id(1)>1){\n"
                      "neighbours += ";
            if (weights[0][0] != 1) {
                result += std::to_string(weights[0][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)-2) * get_global_size(0)]);}";
        }
        if (weights[1][0] != 0) {
            result += "if(get_global_id(1)>0){\n"
                      "neighbours += ";
            if (weights[1][0] != 1) {
                result += std::to_string(weights[1][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)-1) * get_global_size(0)]);}";
        }
        if (weights[2][0] != 0) {
            result += "neighbours += ";
            if (weights[2][0] != 1) {
                result += std::to_string(weights[2][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)) * get_global_size(0)]);";
        }
        if (weights[3][0] != 0) {
            result += "if(get_global_id(1)<get_global_size(1)-1){\n"
                      "neighbours += ";
            if (weights[3][0] != 1) {
                result += std::to_string(weights[3][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)+1) * get_global_size(0)]);}";
        }
        if (weights[4][0] != 0) {
            result += "if(get_global_id(1)<get_global_size(1)-2){\n"
                      "neighbours += ";
            if (weights[4][0] != 1) {
                result += std::to_string(weights[4][0]) + "* ";
            }
            result += "(data[(get_global_id(0)-2)+(get_global_id(1)+2) * get_global_size(0)]);}";
        }
        result += "}\n";
    }

    if (weights[2][3] != 0 && weights[1][3] != 0 && weights[3][3] != 0) {
        result += "if(get_global_id(0) != get_global_size(0)-1){\n";
        if (weights[2][3] != 0) {
            //2D Right
            result += "neighbours += ";
            if (weights[2][3] != 1) {
                result += std::to_string(weights[2][3]) + "*";
            }
            result += "(data[(get_global_id(0)+1) + get_global_id(1) * get_global_size(0)]);";

        }
        if (weights[1][3] != 0) {
            //2D TopRight
            result += "        if (get_global_id(1) != 0){\n"
                      "            neighbours += ";
            if (weights[1][3]) {
                result += std::to_string(weights[1][3]) + "*";
            }
            result += "(data[(get_global_id(0)+1) +(get_global_id(1)-1) * get_global_size(0)]);\n"
                      "        }\n";
        }
        if (weights[3][3] != 0) {
            // 2D BotRight
            result += "        if (get_global_id(1) != get_global_size(1)-1){\n"
                      "            neighbours += ";
            if (weights[3][3]) {
                result += std::to_string(weights[3][3]) + "*";
            }
            result += "(data[(get_global_id(0)+1)+(get_global_id(1)+1) * get_global_size(0)]);\n"
                      "        }\n";
        }
        result += "    }";
    }

    if (weights[0][4] != 0 && weights[1][4] != 0 && weights[2][4] != 0 && weights[3][4] != 0 && weights[4][4] != 0) {
        result += "if(get_global_id(0) < get_global_size(0)-2){\n";
        if (weights[0][4] != 0) {
            result += "if(get_global_id(1)>1){\n"
                      "neighbours += ";
            if (weights[0][4] != 1) {
                result += std::to_string(weights[0][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)-2) * get_global_size(0)]);}";
        }
        if (weights[1][4] != 0) {
            result += "if(get_global_id(1)>0){\n"
                      "neighbours += ";
            if (weights[1][4] != 1) {
                result += std::to_string(weights[1][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)-1) * get_global_size(0)]);}";
        }
        if (weights[2][4] != 0) {
            result += "neighbours += ";
            if (weights[2][4] != 1) {
                result += std::to_string(weights[2][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)) * get_global_size(0)]);";
        }
        if (weights[3][4] != 0) {
            result += "if(get_global_id(1)<get_global_size(1)-1){\n"
                      "neighbours += ";
            if (weights[3][4] != 1) {
                result += std::to_string(weights[3][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)+1) * get_global_size(0)]);}";
        }
        if (weights[4][4] != 0) {
            result += "if(get_global_id(1)<get_global_size(1)-2){\n"
                      "neighbours += ";
            if (weights[4][4] != 1) {
                result += std::to_string(weights[4][4]) + "* ";
            }
            result += "(data[(get_global_id(0)+2)+(get_global_id(1)+2) * get_global_size(0)]);}";
        }
        result += "}\n";
    }


    if (weights[1][2] != 0) {
        // Top
        result += "if(get_global_id(1) != 0){\n"
                  "        neighbours += ";
        if (weights[1][2] != 1) {
            result += std::to_string(weights[1][2]) + "*";
        }
        result += "(data[get_global_id(0)+(get_global_id(1)-1) * get_global_size(0)]);\n"
                  "    }";
    }

    if (weights[0][1] != 0 && weights[0][2] != 0 && weights[0][3] != 0) {
        result += "if(get_global_id(1) > 1){";
        if (weights[0][1] != 0) {
            result += "if(get_global_id(0)> 0){"
                      "neighbours +=";
            if (weights[0][1] != 1) {
                result += std::to_string(weights[0][1]) + "* ";
            }
            result += "(data[(get_global_id(0)-1)+(get_global_id(1)-2) * get_global_size(0)]);}";
        }
        if (weights[0][2] != 0) {
            result += "neighbours +=";
            if (weights[0][2] != 1) {
                result += std::to_string(weights[0][2]) + "* ";
            }
            result += "(data[(get_global_id(0))+(get_global_id(1)-2) * get_global_size(0)]);";
        }
        if (weights[0][3] != 0) {
            result += "if(get_global_id(0)< get_global_size(0)-1){"
                      "neighbours +=";
            if (weights[0][3] != 1) {
                result += std::to_string(weights[0][3]) + "* ";
            }
            result += "(data[(get_global_id(0)+1)+(get_global_id(1)-2) * get_global_size(0)]);}";
        }
        result += "}";
    }

    if (weights[3][2] != 0) {
        //Bot
        result += "if(get_global_id(1) != get_global_size(1)-1){\n"
                  "        neighbours += ";
        if (weights[3][2] != 1) {
            result += std::to_string(weights[3][2]) + "*";
        }
        result += "(data[get_global_id(0) + (get_global_id(1)+1) * get_global_size(0)]);\n"
                  "    }";

    }

    if (weights[4][1] != 0 && weights[4][2] != 0 && weights[4][3] != 0) {
        result += "if(get_global_id(1) < get_global_size(1)-2){";
        if (weights[4][1] != 0) {
            result += "if(get_global_id(0)> 0){"
                      "neighbours +=";
            if (weights[4][1] != 1) {
                result += std::to_string(weights[4][1]) + "* ";
            }
            result += "(data[(get_global_id(0)-1)+(get_global_id(1)+2) * get_global_size(0)]);}";
        }
        if (weights[4][2] != 0) {
            result += "neighbours +=";
            if (weights[4][2] != 1) {
                result += std::to_string(weights[4][2]) + "* ";
            }
            result += "(data[(get_global_id(0))+(get_global_id(1)+2) * get_global_size(0)]);";
        }
        if (weights[4][3] != 0) {
            result += "if(get_global_id(0)< get_global_size(0)-1){"
                      "neighbours +=";
            if (weights[4][3] != 1) {
                result += std::to_string(weights[4][3]) + "* ";
            }
            result += "(data[(get_global_id(0)+1)+(get_global_id(1)+2) * get_global_size(0)]);}";
        }
        result += "}";
    }

    result += "myType state = data[id];\n"
              "\n";

    result += generateEnding("state");
    result += "}";

    return result;
}
