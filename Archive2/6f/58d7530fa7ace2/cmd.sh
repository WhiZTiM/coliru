set -x;
g++-5.1 -std=c++11 -O3 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
# clang++ -std=c++1z -O3 -Wall -Wextra -pedantic -pthread -stdlib=libc++ main.cpp -lsupc++ && ./a.out << A
# clang++ -std=c++14 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp && ./a.out