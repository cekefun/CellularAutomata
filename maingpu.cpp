#include <iostream>
#include <vector>
#include "gpu/GameOfLife.h"
int main(){


    std::vector<std::vector<int>> arr =         {{{0,1,0},
                                                                 {0,1,0},
                                                                 {0,1,0}}};

    GameOfLife gol;
    gol.setSquare();
    gol.setType("int");
    gol.addDirectPattern(0,1,3);
    gol.addDefaultPattern(1,0);
    gol.addRangePattern(1,1,2,3);
    gol.setInitialData(arr);

    for(int i= 0; i< 3; i++){
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
        gol.TimeStep();
        arr = gol.getData();
    }

}
