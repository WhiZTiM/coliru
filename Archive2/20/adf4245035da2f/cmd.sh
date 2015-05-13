##clang++ --version
##g++-4.8 --version
g++-4.9 -std=c++11 -fdump-tree-optimized  -Wall -Wextra -Wconversion -pedantic-errors  -O3 -pthread  main.cpp && ./a.out && cat main.cpp.169t.optimized
##g++ --version
##set -x ; g++-4.9 -std=c++11 -Wall -Wextra -Wconversion -pedantic  -O3  -pedantic  -pthread -S main.cpp && cat main.s 
##set -x ; clang++  -D_GLIBCXX_DEBUG -stdlib=libstdc++ -std=c++11 -fsanitize=undefined -Wall -Wextra -Wconversion  -pedantic main.cpp && ./a.out 
##set -x ; gcc -x c -O2  -fno-aggressive-loop-optimizations -std=c99 -Wall -Wextra -Wconversion -pedantic main.cpp && ./a.out
##set -x ; gcc -x c -std=c99 -O0 -W -Wall -Wextra -Wconversion -pedantic -S main.cpp && cat main.s 
##set -x ; clang -x c -std=c99 -fsanitize=undefined   -Wall -Wextra -Wconversion -O3  -pedantic main.cpp && ./a.out