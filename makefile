FF_ROOT = /home/fabmoore/Documents/fastflow

CXX = g++ -std=c++17
INCLUDES = -I $(FF_ROOT)
CXXFLAGS = -O3 #-fopenmp

LDFLAGS = -pthread
OPTFLAGS = -O3 #-finline-functions -DNDEBUG -ftree-vectorize #-fopt-info-vec-missed -fopt-info-vec

TARGETS = utimer utils create_input_file read_file knn_seq knn_stl knn_fastflow

.PHONY: all clean cleanall
.SUFFIXES: .cpp

%: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OPTFLAGS) -o $@ $< $(LDFLAGS)


all : $(TARGETS)
clean :
	rm -f $(TARGETS)
cleanall : clean
	\rm -f *.o *~ *.csv *txt
