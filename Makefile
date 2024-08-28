# Tair Mazriv
# id: 209188382
# tairmazriv@gmail.com

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -I/usr/include/SDL2 -D_REENTRANT
LIBS = -lSDL2 -lSDL2_ttf

DEMO_SRCS = Demo.cpp
TEST_SRCS = Tests.cpp
HEADERS = tree.hpp node.hpp iterators.hpp treeGUI.hpp complex.hpp
DEMO_OBJS = $(DEMO_SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
DEMO_EXEC = Demo
TEST_EXEC = test

all: $(DEMO_EXEC) $(TEST_EXEC)

$(DEMO_EXEC): $(DEMO_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(DEMO_OBJS) $(TEST_OBJS) $(DEMO_EXEC) $(TEST_EXEC)

tree: all
	./$(DEMO_EXEC)
	./$(TEST_EXEC)

.PHONY: all clean tree
