clang++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
cat ./test.data
clang++ -std=c++14 -O2 -Wall -pedantic -pthread -DCHANGED main.cpp && ./a.out