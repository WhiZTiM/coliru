cat>3test.txt<<TEST; g++ -std=c++11 -Os -Wall -pedantic main.cpp  && ./a.out
t # 0
v 0 5
v 1 32
v 2 6
v 3 91
v 4 8
e 0 1 10
e 0 2 7
e 1 2 24
e 1 4 85
e 2 3 41
e 4 2 4
t # 1
v 0 5
v 1 32
v 2 6
v 3 91
v 4 8
v 5 34
v 6 9
e 0 1 10
e 0 2 7
e 1 2 24
e 1 4 85
e 2 3 41
e 4 2 4
e 4 3 18
e 5 6 95
e 1 6 22
t # 2
v 0 5
v 1 32
v 2 6
v 3 91
v 4 8
e 0 1 10
e 0 2 7
e 1 2 24
e 1 4 85
e 2 3 41
e 4 2 4
t # 3
v 0 15
v 1 132
v 2 16
v 3 191
v 4 18
e 0 1 110
e 0 2 17
e 1 2 124
e 1 4 185
e 2 3 141
e 4 2 14
TEST