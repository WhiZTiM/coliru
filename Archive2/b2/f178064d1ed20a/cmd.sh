set -x; clang++ -stdlib=libc++ -std=c++11 -O3 -march=native -Wall -Wextra -pedantic -pthread main.cpp -lsupc++ && time ./a.out