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
#include "read_file.h"
#include "utils.h"
#include "utimer.cpp"

using namespace std;

// Structure of the operator
// overloading for comparison
struct asc_order {
    constexpr bool operator()(
            pair<float, int> const& a,
            pair<float, int> const& b)
    const noexcept
    {
        return a.first > b.first;
    }
};

int main(int argc, char* argv[]) {

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

            // vector implementation
            // compute and store distance and item in the vector
            for (int j=0; j<data.size(); j++) {
                if (i==j)
                    continue;
                neighbors.push_back(move(make_pair(euclidean_distance(data[i], data[j]), j)));
            }

            // sort neighbors by distance
            make_heap(neighbors.begin(), neighbors.end());
            sort_heap(neighbors.begin(), neighbors.end());

            // take only first k items from sorted neighbors
            vector<pair<float, int>> best_neighbors(neighbors.begin(), neighbors.begin()+k);


            /*// priority queue implementation (better complexity)
            // use priority queue to store the neighbors
            priority_queue<pair<float, int>, vector<pair<float, int>>, asc_order> pqueue;
            for(int j=0; j<data.size(); j++) {
                if(j==i)        // (except itself)
                    continue;
                pqueue.push(move(make_pair(euclidean_distance(data[i], data[j]), j)));
            }
            for (int r=0; r<k; r++) {
                neighbors.push_back(pqueue.top());
                pqueue.pop();
            }*/

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
