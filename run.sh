#!/bin/sh
#g++ -O3 -march=native -mtune=native --fast-math -DNDEBUG main.cpp -o test && ./test
g++ -framework Cocoa -F/System/Library/Frameworks -F/Library/Frameworks -O3 -march=native -mtune=native -DNDEBUG main.cpp -o test && ./test
