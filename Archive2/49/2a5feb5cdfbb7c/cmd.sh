clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors -c -S main.cpp && cat ./main.s
echo ========== && g++ -std=c++14 -O3 -Wall -Wextra -pedantic-errors -c -S main.cpp && cat ./main.s