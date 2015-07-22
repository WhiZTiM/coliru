cat > input.txt <<HERE
Dr John Doe
British
2
Soccer
Swimming
HERE
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out