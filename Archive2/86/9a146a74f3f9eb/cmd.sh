uname -a && dmesg | grep processor
clang++ --version | grep clang && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors -pthread main.cpp && time ./a.out
#echo -e '\n==========\n' && g++ --version | grep GCC && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors -pthread main.cpp && ./a.out