clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread && time ./a.out && md5sum *.cpp