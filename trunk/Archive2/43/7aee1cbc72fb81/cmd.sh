od -A none -t x8 -w256 < /dev/urandom | head | awk '{ print "<" $1 " " $2 "> <" $3 "> <" $4 $5 ">" }' | tee input.txt
clang++ -std=c++11 -Os -Wall -pedantic main.cpp && ./a.out