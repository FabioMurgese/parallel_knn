/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * Standard library parallel implementation of Knn.
 *
 * Usage: ./knn_stl input.csv 20 8
 *          for 8 workers (+1 writer) computing 20-nn over input file
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
#include "utimer.cpp"

using namespace std;

// function for the single worker to execute
void job() {

}

// function for the writer to execute
void print() {

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
    vector<queue<string>*> out(nw);

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
            out[i] = new queue<string>();

            threads.push_back(move(thread([](){
                job();
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
        threads.push_back(move(thread([]() {
            print();
        })));

        // waiting for the threads to finish execution
        for (auto &t: threads) {
            t.join();
        }
    }

    return 0;
}