g++ -std=c++11 -O3 -Wall -pedantic main.cpp && od -A none -t o /dev/urandom | tr -cd '01' | dd bs=1 count=40960 | ./a.out