#title Scheduler with boost::asio::strand (executors, schedulers, dispatch, etc...)
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -ltbbmalloc -lboost_system -lboost_thread && ./a.out