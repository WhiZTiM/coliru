cat>graphs.txt<<TEST; clang++ -std=c++11 -Os -Wall -pedantic main.cpp  && ./a.out
t # 0
v 0 2
v 1 6
v 2 4
v 3 0
v 4 2
v 5 7
v 6 3
v 7 8
v 8 5
v 9 1
e 0 1 0
e 0 2 14
e 0 3 17
e 0 8 16
e 0 4 15
e 1 8 15
e 2 4 14
e 2 6 4
e 2 8 8
e 3 7 4
e 4 5 14
e 6 8 1
e 6 9 16
e 8 9 11
t # 1
v 0 0
v 1 7
v 2 6
v 3 0
v 4 0
v 5 2
v 6 7
v 7 3
v 8 5
e 0 1 19
e 0 2 16
e 0 6 14
e 0 3 18
e 1 3 18
e 1 4 19
e 1 8 19
e 1 7 6
e 2 7 8
e 4 5 4
e 4 8 10
e 7 8 1
t # 2
v 0 4
v 1 7
v 2 5
v 3 4
v 4 8
v 5 3
v 6 0
v 7 8
v 8 4
v 9 3
e 0 1 12
e 0 5 19
e 0 3 19
e 0 6 2
e 0 2 8
e 1 2 9
e 1 4 5
e 2 3 8
e 2 8 14
e 2 9 13
e 3 6 6
e 3 8 19
e 3 5 4
e 4 5 15
e 4 6 18
e 6 7 18
t # 3
v 0 0
v 1 7
v 2 1
v 3 0
v 4 6
v 5 6
v 6 7
e 0 1 19
e 0 2 12
e 0 4 13
e 0 6 19
e 2 3 12
e 2 5 9
e 3 4 16
t # 4
v 0 0
v 1 8
v 2 1
v 3 3
v 4 7
v 5 0
v 6 7
v 7 2
v 8 3
v 9 8
e 0 1 8
e 0 2 12
e 0 4 12
e 0 9 18
e 0 5 18
e 1 3 15
e 1 6 12
e 1 8 15
e 2 9 5
e 3 9 15
e 4 5 12
e 4 8 5
e 5 7 17
e 5 8 4
t # 5
v 0 0
v 1 8
v 2 0
v 3 0
v 4 2
v 5 0
v 6 7
v 7 6
v 8 6
v 9 1
e 0 1 5
e 1 2 14
e 1 3 18
e 1 5 14
e 1 6 2
e 3 4 17
e 3 6 18
e 3 9 12
e 3 8 16
e 4 8 9
e 5 7 8
e 5 9 10
e 6 8 19
e 6 9 4
e 8 9 14
t # 6
v 0 3
v 1 5
v 2 7
v 3 9
v 4 0
v 5 1
v 6 7
v 7 8
v 8 6
e 0 1 13
e 0 2 12
e 0 3 12
e 0 4 4
e 0 6 6
e 1 4 10
e 1 6 12
e 2 5 4
e 2 6 6
e 3 8 11
e 4 5 6
e 6 7 2
t # 7
v 0 0
v 1 6
v 2 1
v 3 7
v 4 2
v 5 8
v 6 1
v 7 7
v 8 0
v 9 0
e 0 1 16
e 0 2 6
e 0 3 14
e 0 7 18
e 1 4 7
e 1 6 14
e 1 8 13
e 2 7 11
e 2 8 12
e 3 5 2
e 3 8 18
e 6 9 10
e 7 9 18
t # 8
v 0 6
v 1 8
v 2 2
v 3 5
v 4 0
v 5 4
v 6 1
v 7 0
v 8 6
v 9 6
v 10 0
e 0 1 1
e 0 2 6
e 0 3 15
e 0 7 1
e 1 4 18
e 1 10 0
e 2 5 8
e 2 9 7
e 2 4 17
e 2 10 17
e 3 8 17
e 4 5 2
e 4 8 16
e 5 6 19
e 5 10 2
e 5 7 2
e 7 8 16
t # 9
v 0 1
v 1 2
v 2 1
v 3 1
v 4 5
v 5 4
v 6 0
v 7 2
v 8 7
e 0 1 17
e 0 4 11
e 0 5 19
e 1 2 3
e 1 3 19
e 2 6 6
e 3 7 17
e 3 4 16
e 4 5 8
e 4 8 12
e 6 8 18
e 7 8 14

TEST