g++ --version
g++ -std=c++14 -pedantic -Wall -Wextra main.cpp && ./a.out
clang++ --version
clang++ -std=c++14 -pedantic -Wall -Wextra -Wno-gnu-zero-variadic-macro-arguments main.cpp && ./a.out