g++-4.8 -std=c++11  -O0 -Wall -Wextra -Wconversion  -pedantic  -pthread -pedantic-errors -fno-builtin main.cpp  && ./a.out
##g++-4.8 -std=c++11  -O0 -Wall -Wextra -Wconversion -S -pedantic  -pthread -pedantic main.cpp  && cat main.s