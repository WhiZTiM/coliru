#title mutex vs spinlock latency
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out