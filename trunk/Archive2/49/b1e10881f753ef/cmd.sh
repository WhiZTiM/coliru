#title Atomic increment benchmark
g++ -std=c++14 -O0 -Wall -pedantic -pthread main.cpp && echo "Using -O0: $(./a.out)"
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && echo "Using -O2: $(./a.out)"