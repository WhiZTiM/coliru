clang++ -S -emit-llvm -std=c++11 -march=corei7 -O2 -Wall -pedantic -pthread main.cpp -o main.ll && cat main.ll && clang++ -S -std=c++11 -march=corei7 -O2 -Wall -pedantic -pthread main.cpp -o main.asm && cat main.asm