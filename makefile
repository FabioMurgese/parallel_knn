FF_ROOT = ./fastflow
#FF_ROOT = /home/fabmoore/Documents/fastflow

CXX = g++ -std=c++17
INCLUDES = -I $(FF_ROOT)
CXXFLAGS = -g #-O3 #-fopenmp

LDFLAGS = -pthread
OPTFLAGS = -O3 -finline-functions #-fopt-info-vec-optimized # -DNDEBUG -ftree-vectorize #-fopt-info-vec-missed -fopt-info-vec

TARGETS = knn_stl knn_fastflow knn_seq #utimer utils create_input_file read_file knn_seq knn_stl knn_fastflow

.PHONY: all clean cleanall
.SUFFIXES: .cpp

all	: $(TARGETS)

knn_fastflow: $(OBJECTS) knn_fastflow.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $(OBJECTS) knn_fastflow.o $(LDFLAGS)

knn_stl: $(OBJECTS) knn_stl.o
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -o $@ $(OBJECTS) knn_stl.o $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ -c $< $(LDFLAGS)

clean	:
	rm -f $(TARGETS)

cleanall	:	clean
	#rm -f *.txt *~
	rm -f *.o *~

cleanoutputs	 :
	rm -f *.txt *~
