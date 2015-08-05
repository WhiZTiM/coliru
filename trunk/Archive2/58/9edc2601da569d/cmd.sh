set -x;
clang++ -stdlib=libc++ -std=c++1y -O0 -Wall -pedantic -pthread main.cpp -fsanitize=undefined -lcxxrt -ldl && ./a.out