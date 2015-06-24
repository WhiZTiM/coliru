#title L3 cache latency measurement
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && for i in {1..5} ; do ./a.out ; done
echo "(on my pc it returns ~25ns)"