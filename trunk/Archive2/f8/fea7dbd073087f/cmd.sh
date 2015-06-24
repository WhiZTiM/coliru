#title Disruptor experiment
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && timeout 3 ./a.out >a 2>b ; cat a ; cat b