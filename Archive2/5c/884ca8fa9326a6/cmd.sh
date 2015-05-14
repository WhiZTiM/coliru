#title Atomic increment under false sharing
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out