/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * */

#include "utils.h"

float euclidean_distance(std::pair<float,float> &p1, std::pair<float,float> &p2) {
    return pow(p2.first - p1.first, 2) + pow(p2.second - p1.second, 2);
}


/*float euclidean_distance(float &x1, float &y1, float &x2, float &y2) {
    return pow(x2 - x1, 2) + pow(y2 - y1, 2);
}*/
