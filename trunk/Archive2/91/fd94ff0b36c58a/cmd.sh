set -x ; g++-4.8 -std=c++11 -c -O3 main.cpp -S -o - | c++filt