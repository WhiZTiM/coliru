clang++ -std=c++11 -O0 -g -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread && time ./a.out && md5sum a.out*