set -x; g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && time ./a.out
clang++ -stdlib=libc++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp -lcxxrt -ldl && time ./a.out