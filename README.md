# parallel_knn
Parallel implementation of KNN algorithm, using C++ standard library and FastFlow.

## Building and running the model
To build and run the project I created a *Makefile*. First, you have to download the Fastflow library inside your working directory and then build the project by using the commands

```
git clone https://github.com/fastflow/fastflow.git
make
```

To test a specific version *executable*

```
./executable inputfile k nworkers
```

To compute the timings needed for the execution of a specific version there is the script *average_time.sh*, that iterates the execution a specified number of times, printing the timings needed for the Knn computation (Workers + Writer) and their average. Use the command


```
./average_time.sh executable inputfile k nworkers niterations
```
