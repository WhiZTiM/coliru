set -x ;
g++-5.1 -std=c++14 -O0 -Wall -pedantic -Wextra -pthread main.cpp && ./a.out
clang++ -std=c++14 -O0 -Wall -pedantic -Wextra -pthread main.cpp -stdlib=libc++ -lsupc++ && ./a.out