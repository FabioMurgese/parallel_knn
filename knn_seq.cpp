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
#include "read_file.h"
#include "utils.h"
#include "utimer.cpp"

using namespace std;

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
            vector<pair<int,float>> neighbors;

            // insert firsts k items without checking
            int stop = 0;
            // check if we need to insert the node itself --> one more iteration
            // otherwise we lose the value of item i==j in next cycle
            if (i<k)
                stop = k+1;
            else
                stop = k;

            // insert k items in vector
            for (int j=0; j<stop; j++) {
                if (i==j)
                    continue;
                neighbors.push_back(move(make_pair(j, euclidean_distance(data[i], data[j]))));
            }

            // use priority queue to store the neighbors
            priority_queue<pair<int, float>> pqueue;
            for (int n=0; n<neighbors.size(); n++) {
                pqueue.push(neighbors[n]);
            }

            // insert all the other points, calculating their distances
            for(int j=stop; j<data.size(); j++) {
                if(j==i)        // (except itself)
                    continue;
                pqueue.push(move(make_pair(j, euclidean_distance(data[i], data[j]))));
            }

            // int psize = pqueue.size();
            // TO-DO sort the priority queue on the second element (ascending order)


            results.append(to_string(i) + ": { " + printNeighbors(neighbors, k) + " }\n");

            /*string r;
            for (int l=0; l<k; l++) {
                r += to_string(neighbors[i].first) + ", ";
            }
            r += to_string(neighbors[k-1].first);

            results.append(to_string(i) + ": { " + r + " }\n");*/
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
