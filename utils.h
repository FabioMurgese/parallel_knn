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


//float euclidean_distance(float &x1, float &y1, float &x2, float &y2);
float euclidean_distance(std::pair<float,float> &p1, std::pair<float,float> &p2);

std::string printNeighbors(std::vector<std::pair<int,float>> &neighbors, int k);

#endif //PARALLEL_KNN_UTILS_H
