set -x;
g++-5.1 -std=c++14 -O3 -Wall -Wextra -pedantic  main.cpp && ./a.out
clang++ -std=c++14 -O3 -Wall -Wextra -pedantic  -stdlib=libc++ main.cpp -lsupc++ && ./a.out