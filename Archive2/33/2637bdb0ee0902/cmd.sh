cat>input.txt<<INPUT
3
"foo" "bar" "bar2"
1.0 5.0 31.0
2.0 6.0 32.0
3.0 7.0 33.0
INPUT
g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out