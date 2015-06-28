set -x
g++ -O3 -fdelete-null-pointer-checks -std=c++11 main.cpp -lcxxrt -ldl && ./a.out