set -x
clang++ -std=c++1y -Wall -Wextra -pedantic-errors -O3 main.cpp && ./a.out
g++ -std=c++1y -Wall -Wextra -pedantic-errors -O3 main.cpp && ./a.out