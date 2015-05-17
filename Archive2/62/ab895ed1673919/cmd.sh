cat>graphs.txt<<TEST; clang++ -std=c++11 -Os -Wall -pedantic main.cpp  && ./a.out
t # 0
v 0 1
v 1 2
v 2 4
v 3 3
e 0 1 11
e 1 2 12
e 1 3 13
e 2 3 14
t # 1
v 0 4
v 1 2
v 2 3
e 0 1 12
e 0 2 14
t # 2
v 0 2
v 1 3
v 2 1
v 3 4
e 0 2 11
e 0 3 12
e 0 2 13
e 1 3 14
e 1 2 15
t # 3
v 0 3
v 1 1
e 0 1 15
t # 4
v 0 22
v 1 33
v 2 44
e 0 1 12
e 1 2 14
TEST