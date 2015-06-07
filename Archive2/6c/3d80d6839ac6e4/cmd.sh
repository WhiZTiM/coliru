set -x; g++ --version; g++ -std=c++1z -O3 -Wall -pedantic -pthread main.cpp && ./a.out
clang++ --version; clang++ -std=c++1z -O3 -Wall -pedantic -pthread main.cpp && ./a.out