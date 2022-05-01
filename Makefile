APP_NAME=othello

OBJS=*.cpp
MAIN_CPP=main.cpp
BENCH_CPP=benchmark.cpp

COMMON_SOURCES = $(filter-out $(MAIN_CPP) $(BENCH_CPP),$(wildcard *.cpp))

CXX = g++ -m64 -std=c++11
CXXFLAGS = -I. -O3 -Wall -Wno-unknown-pragmas -fopenmp

default: $(APP_NAME)

$(APP_NAME): $(COMMON_SOURCES) $(MAIN_CPP)  *.h
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) $(MAIN_CPP)

$(APP_NAME)_bench: $(COMMON_SOURCES) $(BENCH_CPP) *.h
	$(CXX) $(CXXFLAGS) -o $@ $(COMMON_SOURCES) $(BENCH_CPP)

clean:
	/bin/rm -rf *~ *.o $(APP_NAME) $(APP_NAME)_bench *.class
