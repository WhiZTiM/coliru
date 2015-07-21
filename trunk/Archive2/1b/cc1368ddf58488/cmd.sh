echo clang++:
clang++ -std=c++1z -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo g++:
g++ -std=c++1z -O2 main.cpp && ./a.out