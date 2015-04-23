set -x ;
g++-4.9 -std=c++11 -O0 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -fno-elide-constructors main.cpp -pthread && ./a.out
# clang++ -std=c++14 -O0 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -fno-elide-constructors -stdlib=libc++ main.cpp -lsupc++&& ./a.out
# clang++ -std=c++14 -O3 -Wall -pedantic -Wextra -pthread -Wno-unused-variable -Wno-unused-parameter -Wconversion main.cpp && ./a.out