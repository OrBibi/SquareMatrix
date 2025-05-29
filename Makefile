CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

all: Main

main: main/Main.cpp src/SquareMat.cpp
	$(CXX) $(CXXFLAGS) -o Main main/Main.cpp src/SquareMat.cpp

Main: main
	./Main

test_bin: test/test_SquareMat.cpp src/SquareMat.cpp
	$(CXX) $(CXXFLAGS) -o test_bin test/test_SquareMat.cpp src/SquareMat.cpp

test: test_bin
	./test_bin

valgrind: test_bin
	valgrind --leak-check=full ./test_bin

clean:
	rm -f Main test_bin
