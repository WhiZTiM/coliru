g++-4.8 -std=c++11 -O3 -Wall -pedantic -pthread main.cpp; for X in `seq 1 3`; do echo "TEST $X:"; ./a.out; echo "-------------"; done