set -x
g++ -std=c++11 -o m main.cpp -O3 -Wall -Wextra
echo "2 2 1 2 3 4" | ./m