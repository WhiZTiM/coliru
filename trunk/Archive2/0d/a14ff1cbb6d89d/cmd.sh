clang++ -std=c++1z -O3 -Wall -Wextra -pedantic -pthread main.cpp -fsanitize=undefined && valgrind ./a.out