set -x; g++ -std=c++14 -O3 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out; echo $?
clang++ -std=c++14 -O3 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out; echo $?