#title Vector and Map with small buffer optimizations RPC serialization
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp
timeout 4 ./a.out || echo Program timeout.