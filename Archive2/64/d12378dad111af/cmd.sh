clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread  && ./a.out& (for a in {1..1000}; do nc 127.0.0.1 5050& done)