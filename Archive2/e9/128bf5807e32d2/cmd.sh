#title measuring inter-core latency
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && for i in {1..3} ; do ./a.out ; done
echo "on my pc it returns ~25ns"