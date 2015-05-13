cat>2.txt<<TEST; clang++ -std=c++11 -Os -Wall -pedantic main.cpp  && ./a.out
t # 0
v 0 4
v 1 2
v 2 3
e 0 1 12
e 0 2 14
e 1 2 13
t # 1
v 0 1
v 1 2
v 2 4
v 3 3
e 0 1 11
e 1 2 12
e 1 3 13
e 2 3 14
TEST