g++ -std=c++11 -O2 -Wall -pthread -pedantic main.cpp -lboost_system -lboost_chrono -o test
TZ='America/Detroit' ./test
TZ='Asia/Kathmandu' ./test