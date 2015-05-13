cat>3test.txt<<TEST; clang++ -std=c++11 -Os -Wall -pedantic main.cpp  && ./a.out
t # 0
v 0 4
v 1 2
v 2 3
e 0 1 12
e 0 2 14
t # 1
v 0 1
v 1 2
v 2 4
v 3 3
e 1 2 12
e 1 3 13
e 3 2 14
TEST