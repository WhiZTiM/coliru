clang++ -O2 -Wall -std=c++1y -pedantic -pthread main.cpp && ./a.out | c++filt -t