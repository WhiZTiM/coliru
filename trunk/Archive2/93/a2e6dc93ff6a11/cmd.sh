set -x ;
g++-4.9 -std=c++11 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter main.cpp -pthread && ./a.out
# clang++ -std=c++14 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -stdlib=libc++ main.cpp -lsupc++&& ./a.out
# clang++ -std=c++14 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter main.cpp && ./a.out