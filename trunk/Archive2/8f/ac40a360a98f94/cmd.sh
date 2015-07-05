cat>input.txt<<INPUT
"foo" "bar" "bar2"
1.0 2.0 3.0
1.0 2.0 3.0
1.0 2.0 3.0
INPUT
clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp -lboost_system -lboost_thread && ./a.out