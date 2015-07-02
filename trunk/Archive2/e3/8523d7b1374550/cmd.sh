#title Benchmark: branch predictor vs branchless code
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out | column -t