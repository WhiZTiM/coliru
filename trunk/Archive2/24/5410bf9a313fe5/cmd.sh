set -x ; clang++ -isystem /usr/include/qt4 -std=c++11 -O2 -Wall -pedantic -lQtCore main.cpp && ./a.out