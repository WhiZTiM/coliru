clang++ -std=c++14 -stdlib=libc++ -Wall -Wextra -pedantic-errors main.cpp -otest && ./test
echo -e '\n========\n' && g++ -std=c++14 -Wall -Wextra -pedantic-errors main.cpp -otest && ./test