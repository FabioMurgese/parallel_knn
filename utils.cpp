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
std::string write_best_neighbors(std::vector<std::pair<float, int>> &neighbors, int k) {
    std::string best_neighs;
    // iterate until last but one item to better format the string without comma in the end
    for(int i=0; i < k - 1; i++) {
        best_neighs += std::to_string(neighbors[i].second+1) + ", ";  // add 1 because input file counting starts from 1
    }
    return (best_neighs += std::to_string(neighbors[k - 1].second+1));
}
