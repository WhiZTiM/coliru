set -x ;
clang++ -O3 -pedantic -Wall -Wextra -Wconversion -std=c++1y -stdlib=libc++ -pthread main.cpp -lsupc++ && ./a.out
g++-4.8 -O3 -pedantic -Wall -Wextra -Wconversion -std=c++1y -pthread main.cpp && ./a.out