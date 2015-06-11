clang++ -std=c++14 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo ok
echo ------------ && g++ -std=c++14 -O2 -Wall -Wextra -pedantic-errors -c main.cpp && echo ok