set -x; mv main.{cpp,mm}; clang++ -std=c++11 -Wall -Werror -Wextra -pedantic-errors main.mm && ./a.out