clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp &&./a.out
echo ------------ && g++ -std=c++14 -g -O0 -Wall -Wextra -pedantic-errors main.cpp &&./a.out