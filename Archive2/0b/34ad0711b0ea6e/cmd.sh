g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp       && ./a.out > a.txt
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -DWAT && ./a.out > b.txt
pr -m -t a.txt b.txt