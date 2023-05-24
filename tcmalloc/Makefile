CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -DNDEBUG
ASMCXXFLAGS = -S

BENCHMARK_SRC = benchmark.cpp
BENCHMARK_BIN = benchmark

.PHONY: all build run clean

all: build

build:
	$(CXX) $(CXXFLAGS) $(BENCHMARK_SRC) -o $(BENCHMARK_BIN) -lbenchmark -lpthread -ltcmalloc

asm:
	$(CXX) $(CXXFLAGS) $(BENCHMARK_SRC) $(ASMCXXFLAGS)

run:
	./$(BENCHMARK_BIN)

clean:
	rm -f $(BENCHMARK_BIN)