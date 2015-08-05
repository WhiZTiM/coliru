#title How by-ref params can slow down your code and why inline functions are cool.
g++ -std=c++11 -c -O2 -Wall -pedantic main.cpp -S -masm=intel -o - | c++filt | grep -v '\.'