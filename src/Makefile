CXX = g++
CXXFLAGS = -std=c++20 -Wall -Werror=vla -g 
EXEC = cc3k
SRCS = $(wildcard *.cc) $(wildcard enemy/*.cc) $(wildcard gold/*.cc) $(wildcard player/*.cc)
OBJS = $(SRCS:.cc=.o)

.PHONY: all clean

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

clean:
	rm -f $(OBJS) $(EXEC)
