set -x;
g++-5.1 -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp && ./a.out
# clang++ -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -Wconversion -pthread main.cpp && ./a.out
# clang++ -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread -stdlib=libc++ main.cpp -lsupc++ && ./a.out