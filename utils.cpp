/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * */

#include "utils.h"

float euclidean_distance(std::pair<float,float> &p1, std::pair<float,float> &p2) {
    return pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2);
}

// prints the first K neighbors in a vector, concatenating them with a ", "
std::string printNeighbors(std::vector<std::pair<int,float>> &neighbors, int k) {
    std::string res;
    for(int i=0; i < k - 1; i++) {
        res += std::to_string(neighbors[i].first) + ", ";
    }
    return (res += std::to_string(neighbors[k - 1].first));
}


/*float euclidean_distance(float &x1, float &y1, float &x2, float &y2) {
    return pow(x2 - x1, 2) + pow(y2 - y1, 2);
}*/
