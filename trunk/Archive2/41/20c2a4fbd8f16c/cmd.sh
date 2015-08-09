clang++ --version | grep clang && clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
g++ --version | grep GCC && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
g++-5.1 --version | grep GCC && g++-5.1 -std=c++14 -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out
g++-4.9 --version | grep GCC && g++-4.9 -std=c++14 -O3 -Wall -Wextra -pedantic-errors main.cpp && ./a.out