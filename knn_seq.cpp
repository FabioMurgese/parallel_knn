/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * */

#include <cstdlib>
#include <vector>
#include <queue>
#include "read_file.h"
#include "utils.h"
#include "utimer.cpp"

using namespace std;

int main(int argc, char* argv[]) {

    char *file_name = argv[1];          // input file name
    int k = atoi(argv[2]);         // k param
    vector<pair<float,float>> data;     // structure to populate from input file

    {
        utimer test("Reading input file");
        // Populate the structure
        data = ReadFile(file_name);
    }

    // string to save all results
    string results = "";

    {
        utimer knn("Knn");
        for (int i=0; i<data.size(); i++) {
            // store neighbors for each data point
            vector<pair<int,float>> neighbors;

            // insert first k items without checking
            int temp = 0;
            if (i<k)
                temp = k++;
            else
                temp = k;

            // insert k items
            for (int j=0; j<temp; j++) {
                if (i==j)
                    continue;

                // insert elements in vector
                neighbors.push_back(move(make_pair(j, euclidean_distance(data[i], data[j]))));
            }

            priority_queue<pair<int, float>> pqueue;
            for (int n=0; n<neighbors.size(); n++) {
                pqueue.push(neighbors[n]);
            }


        }


    }
    return 0;
}
