clang++ -std=c++14 -stdlib=libc++ -Wall -Wextra -pedantic-errors -c -S -O3 main.cpp && cat main.s
echo ============================================
g++ -std=c++14 -Wall -Wextra -pedantic-errors -c -S -O3 main.cpp && cat main.s