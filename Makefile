CXX=g++
CXXFLAGS=-std=c++11

INCLUDES=-isystem ../benchmark/include
LFLAGS=-L../benchmark/build/src -lbenchmark -lpthread

all: cacheBench

cacheBench: cacheBench.cc
	 $(CXX) cacheBench.cc $(CXXFLAGS) $(INCLUDES) $(LFLAGS) -o cacheBench

clean:
	rm cacheBench
