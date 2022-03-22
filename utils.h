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

float euclidean_distance(std::pair<float,float> &p, std::pair<float,float> &q);

std::string write_best_neighbors(std::vector<std::pair<float, int>> &neighbors, int k);

#endif //PARALLEL_KNN_UTILS_H
