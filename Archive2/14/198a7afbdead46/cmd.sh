set -x;
clang++ -std=c++1y -O3 -Wall -pedantic -pthread main.cpp -stdlib=libc++ && ./a.out
g++ -std=c++1y -O3 -Wall -pedantic -pthread main.cpp && ./a.out