set -x ; clang++ -std=c++11 -O3 -Wall -pedantic main.cpp -lboost_chrono -lboost_system && ./a.out |& c++filt -t