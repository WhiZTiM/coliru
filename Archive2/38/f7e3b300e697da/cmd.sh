netcat -l 127.0.0.1 8087 <<< 'this could be a valid JSON response'& clang++ -std=c++11 -Wall -pthread main.cpp -lboost_system && ./a.out