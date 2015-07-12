g++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread && ./a.out& sleep 1; netcat 127.0.0.1 6767 <<HERE
TEST

HERE