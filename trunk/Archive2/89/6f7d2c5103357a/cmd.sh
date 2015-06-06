g++ -std=c++11 -O2 -Wall -pedantic main.cpp -lboost_system -lboost_thread 
./a.out& sleep .5; netcat 127.0.0.1 6666 < main.cpp