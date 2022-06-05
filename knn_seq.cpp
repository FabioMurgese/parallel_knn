/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * Usage: ./knn_seq input.csv 20
 * */

#include <cstdlib>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "read_file.cpp"
#include "utils.cpp"
#include "utimer.cpp"

using namespace std;


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " + string (argv[0]) + " input_file k" << endl;
        return -1;
    }

    char *file_name = argv[1];          // input file name
    int k = atoi(argv[2]);         // k param
    vector<pair<float,float>> data;     // structure to populate from input file

    {
        utimer reader("Reading input file");
        // populate the structure
        data = ReadFile(file_name);
    }

    // string to save all results
    string results = "";

    {
        utimer knn("Knn");
        for (int i=0; i<data.size(); i++) {
            // vector to store neighbors for each data point
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

            results.append(to_string(i+1) + ": { " + write_best_neighbors(neighbors, k) + " }\n");
        }
    }

    {
        utimer writer("Writing to output file");

        ofstream output;
        output.open("output_sequential.txt");
        if (!output.is_open()) {
            std::cerr << "Failed to open output file. Exiting." ;
        }
        output << results;      // write to output file
        output.close();
    }

    return 0;
}
