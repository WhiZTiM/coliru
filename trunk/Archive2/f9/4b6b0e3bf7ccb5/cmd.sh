set -x; g++ -std=c++1z -O3 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ -std=c++1z -O3 -stdlib=libc++ -Wall -pedantic -pthread main.cpp && ./a.out