clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo -e '\nclang++ compiled this without errors\n'
g++-4.9 -std=c++11 -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo -e '\ng++ compiled this without errors\n'