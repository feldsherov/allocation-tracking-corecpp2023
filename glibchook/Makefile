CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -DNDEBUG
ASMCXXFLAGS = -S

HOOK_SRC = hook.cpp
HOOK_BIN = hook

.PHONY: all build run clean

all: build

build:
	$(CXX) $(CXXFLAGS) $(HOOK_SRC) -o $(HOOK_BIN) 

asm:
	$(CXX) $(CXXFLAGS) $(HOOK_SRC) $(ASMCXXFLAGS)

run:
	./$(HOOK_BIN)

clean:
	rm -f $(HOOK_BIN)