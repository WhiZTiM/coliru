#title Using std::future for non-threaded async.
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread && ./a.out