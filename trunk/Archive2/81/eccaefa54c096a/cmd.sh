clang++ -std=c++11 -S -O3 -march=native -Wall -pedantic -pthread main.cpp -o a.s && cat a.s