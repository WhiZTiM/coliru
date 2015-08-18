set -x; # g++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -std=c++11 -O3 -stdlib=libc++ -Wall -pedantic -pthread main.cpp && ./a.out