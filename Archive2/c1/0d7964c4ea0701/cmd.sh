set -x
clang++ -O2 -stdlib=libc++ -std=c++11 main.cpp -lcxxrt -ldl && ./a.out