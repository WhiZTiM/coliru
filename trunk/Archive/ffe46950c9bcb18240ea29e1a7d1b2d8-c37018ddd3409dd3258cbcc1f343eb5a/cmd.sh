g++ -S -O0 main.cpp -o a ;g++ -S -O3 main.cpp -o b ; diff -y a b