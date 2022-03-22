/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * FastFlow parallel implementation of Knn.
 *
 * Usage: ./knn_stl input.csv 10 4
 *          for 4 workers computing 10-nn over input file
 * */

#include <cstdlib>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <thread>
#include "read_file.h"
#include "utils.h"
#include "myqueue.cpp"
#include "utimer.cpp"

#include <ff/parallel_for.hpp>

using namespace std;

int main(int argc, char* argv[]) {

    if (argc < 4) {
        cout << "Usage: " + string (argv[0]) + " input_file k nw" << endl;
        return -1;
    }

    char* name = argv[1];               // input file
    int k = atoi(argv[2]);         // k parameter
    int nw = atoi(argv[3]);        // number of workers

    vector<pair<float,float>> data;     // points

    {
        utimer reader("Reading input file");
        data = ReadFile(name);
    }

    ff::ParallelForReduce<string> pfr(nw);
    string results = "";

    {
        utimer knn("Knn");
        pfr.parallel_reduce(results, "", 0, data.size(), 1, 0,
                            [&](const long i, string &mystring) {
            vector<pair<float, int>> neighbors;
            // compute and store distance and item in the vector
            for (int j=0; j<data.size(); j++) {
                if (i==j)
                    continue;
                neighbors.push_back(move(make_pair(euclidean_distance(data[i], data[j]), j)));
            }
            // sort neighbors by distance
            make_heap(neighbors.begin(), neighbors.end());
            sort_heap(neighbors.begin(), neighbors.end());

            mystring.append(to_string(i+1) + ": { " + write_best_neighbors(neighbors, k) + " }\n");
            },
            [](string &finalstring, const string e) {
                finalstring.append(e);
            });

        ofstream outfile;
        outfile.open ("output_ff.txt");
        outfile << results;
        outfile.close();
    }

    return 0;
}