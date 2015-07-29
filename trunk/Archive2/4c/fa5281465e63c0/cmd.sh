clang++ -std=c++14 -stdlib=libc++ -Wall -Wextra -pedantic-errors -O3 main.cpp && ./a.out <<< '11 12  13 14  15 16  17 18  19 20  21 22  23 24'
echo ============================================
g++ -std=c++14 -Wall -Wextra -pedantic-errors main.cpp && ./a.out <<< '11 12  13 14  15 16  17 18  19 20  21 22  23 24'