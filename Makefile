APP_NAME=othello

OBJS=*.cpp

CXX = g++ -m64 -std=c++11
CXXFLAGS = -I. -O3 -Wall -Wno-unknown-pragmas

default: $(APP_NAME)

$(APP_NAME): $(OBJS) *.h
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

clean:
	/bin/rm -rf *~ *.o $(APP_NAME) *.class
