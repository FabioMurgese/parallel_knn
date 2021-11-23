/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * */

#include "read_file.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Read the input file and populate the data vector
vector<pair<float,float>> ReadFile(char* name) {
    ifstream input(name);
    if (!input.is_open()) {
        cerr << "Failed to open " << name << "... Exiting." << endl;
        exit(-1);
    }

    vector<pair<float,float>> data;
    float x, y;
    char comma;

    while (input >> x >> comma >> y) {  // point: <x, y>
        data.push_back(make_pair(x, y));
    }

    input.close();
    if(data.size() < 1) {
        cerr << name << " seems empty... Exiting." << endl;
        exit(-2);
    }
    return data;
}
