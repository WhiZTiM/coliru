clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O2 main.cpp -lsupc++ && ./a.out <<< 123
echo --------------- && g++-4.8 -std=c++11 -Wall -Wextra -pedantic-errors -O2 main.cpp && ./a.out <<< 123