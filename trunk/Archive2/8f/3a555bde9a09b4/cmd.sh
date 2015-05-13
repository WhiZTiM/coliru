cat>3test.txt<<TEST; clang++ -std=c++11 -Os -Wall -pedantic main.cpp  && ./a.out
t # 0
v 0 35
v 1 47
v 2 15
e 0 1 10
e 0 2 77
t # 1
v 0 35
v 1 15
v 2 47
e 0 2 10
e 0 1 77
TEST