echo -e '\n-------------------------------------\n'
cat -n main.cpp
g++-4.8 -std=c++11 -Wall -Wextra -pedantic-errors -O3 main.cpp && ./a.out
echo -e '\n-------------------------------------\n'
cat -n temp.txt