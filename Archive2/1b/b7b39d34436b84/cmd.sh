#title Sleep first, switch to spinning in the last 10 microseconds.
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out