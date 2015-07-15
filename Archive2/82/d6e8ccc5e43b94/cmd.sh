clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out <<INPUT
col 0  "a"  "type" "function" true "name"
col 1  "b"  "type1" "function1" false "name2"
col 2  "c"  "type1" "function2" true "name2"
 
# mapping table
map "a" ("blah", 1) , ("muq", 4) , ("foo", 3)
map "c" ("blah", 1) , ("muq", 4) , ("foo", 3)
map "b" ("blah", 1) , ("muq", 4) , ("foo", 3)
 
# data comment
0    1    2
"a" "b" "c"
0    0   1
1    4   4
INPUT