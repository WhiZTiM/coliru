clang++ -std=c++11 -stdlib=libc++ -O2 -Wall -Wextra -pedantic-errors main.cpp -lsupc++ 
echo '*** output to stdio from program ***' && ./a.out
echo ' *** contents of file temp.txt ***' && cat temp.txt