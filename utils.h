/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * */

#ifndef PARALLEL_KNN_UTILS_H
#define PARALLEL_KNN_UTILS_H

#include <cmath>
#include <vector>
#include <string>

float euclidean_distance(std::pair<float,float> &p1, std::pair<float,float> &p2);

std::string write_best_neighbors(std::vector<std::pair<float, int>> &neighbors, int k);

#endif //PARALLEL_KNN_UTILS_H
