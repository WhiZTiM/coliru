#title Benchmark: branch predictor vs branchless code
g++ -std=c++14 -O3 -Wall -pedantic   -march=native main.cpp && ./a.out | column -t