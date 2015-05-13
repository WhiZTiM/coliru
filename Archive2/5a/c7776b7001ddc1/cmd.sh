g++ -std=c++03 -O2 -Wall -pedantic -DCRAPPY_COMPILER -pthread main.cpp > cpp03.txt 2>&1
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp > cpp11.txt 2>&1
pr -m -W 240 -t cpp03.txt cpp11.txt