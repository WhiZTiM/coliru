set -x ;
g++-4.8 -std=c++11 -O0 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wno-unused-but-set-variable main.cpp && ./a.out