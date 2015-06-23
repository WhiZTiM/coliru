echo -e "g++\n"
g++ -std=c++11 -O0 -Wall -pedantic main.cpp && ./a.out
echo -e "clang++\n"
clang++ -std=c++11 -O0 -Wall -pedantic main.cpp && ./a.out