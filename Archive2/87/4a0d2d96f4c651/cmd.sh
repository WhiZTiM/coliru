echo '[{"number": 1234, "string": "hello world"},{"number": 5678, "string": "foo bar"}]' > input.txt
clang++ -std=c++11 -Os -Wall -pedantic -pthread main.cpp && ./a.out