g++ -std=c++11 main.cpp -S -O3 && cat main.s | grep print_n | wc -l