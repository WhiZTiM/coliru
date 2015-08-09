clang++ -std=c++14 -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -lsupc++ && time ./a.out
echo -e '\n=============\n' && g++ -std=c++14 -Wall -Wextra -pedantic-errors main.cpp && time ./a.out