clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 main.cpp -lsupc++ -o test && ./test
echo --------------- && g++-4.9 -std=c++11 -Wall -Wextra -pedantic-errors -O3 main.cpp -o test && ./test