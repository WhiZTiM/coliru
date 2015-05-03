echo clang:
clang++ -std=c++1z -O3 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
echo gcc:
g++ -std=c++14 -O3 -Wall -Wpedantic main.cpp && ./a.out