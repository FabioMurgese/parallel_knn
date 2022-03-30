FF_ROOT = ./fastflow

CXX = g++ -std=c++17
INCLUDES = -I $(FF_ROOT)
CXXFLAGS = -g #-fopenmp

LDFLAGS = -pthread
OPTFLAGS = -O3 -finline-functions #-fopt-info-vec-optimized # -DNDEBUG -ftree-vectorize #-fopt-info-vec-missed -fopt-info-vec

TARGETS = knn_stl knn_fastflow knn_seq

.PHONY: all clean cleanall
.SUFFIXES: .cpp

all	: $(TARGETS)

knn_fastflow: $(OBJECTS) knn_fastflow.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $(OBJECTS) knn_fastflow.o $(LDFLAGS)

knn_stl: $(OBJECTS) knn_stl.o
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -o $@ $(OBJECTS) knn_stl.o $(LDFLAGS)
	
knn_seq: $(OBJECTS) knn_seq.o
	$(CXX) $(CXXFLAGS) $(OPTFLAGS) -o $@ $(OBJECTS) knn_seq.o $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ -c $< $(LDFLAGS)

clean	:
	rm -f $(TARGETS)

cleanall	:	clean
	rm -f *.o *~

cleanoutputs	 :
	rm -f *.txt *~
