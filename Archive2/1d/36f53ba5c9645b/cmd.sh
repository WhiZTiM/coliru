clang++ -v -O3 -std=c++1y -Wall -fsanitize=undefined -Wextra -pedantic -pthread main.cpp && ./a.out; echo $?