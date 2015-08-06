echo ------------------ With Optimization ------------------
clang++ -std=c++14 -S -emit-llvm -o - -O2 -Wall -pedantic main.cpp
echo ------------------ Without Optimization ------------------
clang++ -std=c++14 -S -emit-llvm -o - -O0 -Wall -pedantic main.cpp