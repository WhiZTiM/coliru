set -x ;
g++-5.1 -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp && ./a.out
clang++ -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp -stdlib=libc++ -lsupc++&& ./a.out
# clang++ -std=c++14 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter main.cpp && ./a.out