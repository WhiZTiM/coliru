set -x
clang++ -std=c++14 -Wall -Wextra -pedantic main.cpp && ./a.out
echo =====
g++ -std=c++14 -Wall -Wextra -pedantic main.cpp && ./a.out