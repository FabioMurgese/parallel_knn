/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * Standard library parallel implementation of Knn.
 *
 * Usage: ./knn_stl input.csv 10 4
 *          for 4 workers (+1 writer) computing 10-nn over input file
 * */

#include <cstdlib>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <thread>
#include "read_file.cpp"
#include "utils.cpp"
#include "myqueue.cpp"
#include "utimer.cpp"

using namespace std;

// function for the single worker to execute
void job(vector<pair<float,float>> &data, int k, vector<myqueue<string>*> &out,
         int nw, int threadid, int size) {

    myqueue<string>* myqueue = out[threadid];

    for (int i=threadid; i<size; i+=nw) {
        // list where will be stored neighbors for element i
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

        myqueue->push(to_string(i+1) + ": { " + write_best_neighbors(neighbors, k) + " }\n");
    }
    // notify termination status
    myqueue->push("");
}

// function for the writer to execute
void print(vector<myqueue<string>*> &out, int nw) {
    string s = "";
    string to_flush = "";

    ofstream outfile;
    outfile.open("output_stl.txt");

    int current = 0;
    int previous = 0;

    // for each worker running
    while (nw > 0) {

        // pop from current queue
        to_flush = out[current]->pop();

        previous = current;
        current = (current+1) % nw;

        if (to_flush == "") {
            // erase the EOS previously received
            out.erase(out.begin()+previous);
            nw--;  // decrease number of workers

            if (current == nw) {
                current = 0;
            }
        } else {
            s.append(to_flush);
        }
    }
    // write and close file
    outfile << s << endl;
    outfile.close();
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Usage: " + string (argv[0]) + " input_file k nw" << endl;
        return -1;
    }

    char* name = argv[1];               // input file
    int k = atoi(argv[2]);         // k parameter
    int nw = atoi(argv[3]);        // number of workers

    vector<thread> threads;             // workers
    vector<pair<float, float>> data;    // points
    vector<myqueue<string>*> out(nw);

    {
        utimer reader("Reading input file");
        data = ReadFile(name);
    }

    int size = data.size();

    {
        utimer knn("Knn");

        // number of workers as nw
        for (int i=0; i<nw; ++i) {
            // output queue for the single worker
            out[i] = new myqueue<string>();

            threads.push_back(move(thread([&data, k, &out, nw, i, size](){
                job(data, k, out, nw, i, size);
            })));

            // Create a cpu_set_t object representing a set of CPUs. Clear it and mark
            // only CPU i as set.
            cpu_set_t cpuset;
            CPU_ZERO(&cpuset);
            CPU_SET(i, &cpuset);
            // Give the native handler a mask that tells on which core the thread should run
            int rc = pthread_setaffinity_np(threads[i].native_handle(), sizeof(cpu_set_t), &cpuset);
            if (rc != 0) {  // Of course, we'll be limited by Hardware and this can fail
                std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
                // std::cerr << "Warning: thread " << i << " isn't set to a specific CPU: setaffinity returned " << rc << "\n";
            }
        }

        // writer to clear out the queues
        threads.push_back(move(thread([&out, nw]() {
            print(out, nw);
        })));

        // waiting for the threads to finish execution
        for (auto &t: threads) {
            t.join();
        }
    }

    return 0;
}
