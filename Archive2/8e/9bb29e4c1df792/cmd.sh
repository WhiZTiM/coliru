f() { g++ -D${1} -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out && ./a.out && ./a.out; }
printf "Normal mutex:\n$(f NORMAL_MUTEX)\n\n"
printf "Adaptive mutex:\n$(f ADAPTIVE_MUTEX)\n\n"
printf "(Larger counter means faster.)"