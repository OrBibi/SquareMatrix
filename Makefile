CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Default target
all: Main

# Build the main executable into bin/Main
Main: bin/Main
	./bin/Main

bin/Main: main/Main.cpp src/SquareMat.cpp
	mkdir -p bin
	$(CXX) $(CXXFLAGS) -o bin/Main main/Main.cpp src/SquareMat.cpp

# Compile unit tests
test_bin: test/test_SquareMat.cpp src/SquareMat.cpp
	$(CXX) $(CXXFLAGS) -o test_bin test/test_SquareMat.cpp src/SquareMat.cpp

# Run unit tests
test: test_bin
	./test_bin

# Run tests with memory leak checks
valgrind: test_bin
	valgrind --leak-check=full ./test_bin

# Clean compiled files
clean:
	rm -f bin/Main test_bin
