set -x ; 
clang++ -std=c++1y -O3 -Wall -pedantic -Wextra -pthread main.cpp && ./a.out