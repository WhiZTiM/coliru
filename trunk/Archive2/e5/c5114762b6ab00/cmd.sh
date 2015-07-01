#title lock vs spinlock and latencies
{ g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out && ./a.out && ./a.out
g++ -DSPINLOCK -std=c++11
 -O2 -Wall -pedantic -pthread main.cpp && ./a.out && ./a.out && ./a.out ; } | column -t