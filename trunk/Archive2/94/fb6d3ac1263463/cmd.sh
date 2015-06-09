#title Self-benchmarking code using recursion into self with modified template argument.
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && timeout 5 ./a.out | head -n10000