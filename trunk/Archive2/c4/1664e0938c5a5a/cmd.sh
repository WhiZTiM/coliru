g++ main.cpp; echo 1 2 3 | ./a.out; g++ -O2 -S -masm=intel -o - main.cpp