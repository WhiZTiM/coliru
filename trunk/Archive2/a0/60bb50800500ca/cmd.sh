#title Asio scheduler with future polling
g++ -std=c++14 -O0 -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread && ./a.out