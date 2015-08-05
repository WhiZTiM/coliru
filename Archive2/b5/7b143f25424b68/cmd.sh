#title min with many params.
g++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp -S -o - -masm=intel  | c++filt | grep -v '\.'