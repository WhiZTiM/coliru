echo gcc && gcc -O3 -x c -std=c11 -Wall -Wextra -pedantic main.cpp && ./a.out
echo clang && clang -O3 -x c -std=c11 -Wall -Wextra -pedantic main.cpp && ./a.out