clang++ -std=c++14 -stdlib=libc++ -O3 -Wall -Wextra -pedantic-errors -pthread main.cpp && echo ok
echo ============== && sleep 2 && g++ -std=c++14  -O3 -Wall -Wextra -pedantic-errors -pthread main.cpp && echo ok