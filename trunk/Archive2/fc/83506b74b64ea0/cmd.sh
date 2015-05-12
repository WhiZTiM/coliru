set -x;
g++-5.1 -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp -lboost_system && ./a.out
# clang++ -std=c++14 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread -stdlib=libc++ main.cpp -lsupc++ -lboost_system && ./a.out
# clang++ -std=c++14 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -Wconversion -pthread main.cpp && ./a.out