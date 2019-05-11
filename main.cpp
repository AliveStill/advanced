#include <iostream>
#include "WeightGraph.h"

using namespace std;

int main()
{
    ///构建了一个如下的图, 对其施加迪杰斯特算法
    /*             12
            1  --------  2
            | \         / |
         8  |  \ 5    5/  |20
            |   \     /   |
            4      3      5
             \     |     /
             4\   8|    /9
               \   |   /
                   6
    */
    WeightGraph wg(6);
    wg.addWeights(0, 1, 12);
    wg.addWeights(0, 2, 5);
    wg.addWeights(0, 3, 8);
    wg.addWeights(1, 2, 5);
    wg.addWeights(1, 4, 20);
    wg.addWeights(2, 3, 6);
    wg.addWeights(2, 5, 8);
    wg.addWeights(3, 5, 4);
    wg.addWeights(2, 4, 10);
    wg.addWeights(4, 5, 9);
    std::cout << wg.dijkstra(0, 5) << std::endl;
    std::cout << wg.dijkstra(0, 4) << std::endl;
    std::cout << wg.dijkstra(0, 3) << std::endl;
    std::cout << wg.dijkstra(0, 2) << std::endl;
    std::cout << wg.dijkstra(0, 1) << std::endl;
    std::cout << wg.dijkstra(0, 0) << std::endl;
    return 0;
}
