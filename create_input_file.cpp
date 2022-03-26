/*
 * Parallel and Distributed Systems 2020/2021
 * @author Fabio Murgese
 *
 * Usage: ./create_input_file 10000 100 123 name_file.csv
 * */

#include <iostream>
#include <fstream>
#include <cmath>

void GenerateFile(int len, int max, int seed, char* name) {

    // Set the seed
    srand(seed);

    // Create file with "name"
    std::ofstream file;
    file.open(name);

    // Generate points
    for (int i=0; i<len; i++) {
        std::pair<float,float> point;
        point = std::make_pair(
                // Use max as maximum span for the generated numbers
                (float)rand() / (float)(RAND_MAX/max),
                (float)rand() / (float)(RAND_MAX/max)
                );
        // Write points to previously created file
        file << point.first << "," << point.second << std::endl;
    }
    // Close file
    file.close();

}

int main (int argc, char* argv[]) {

    int len = atoi(argv[1]);
    int max = atoi(argv[2]);
    int seed = atoi(argv[3]);
    char* name = argv[4];
    GenerateFile(len, max, seed, name);

    return 0;
}


