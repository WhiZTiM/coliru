ln -s /Archive2/d5/cd447d5c993d18/main.cpp test.h
ln -s /Archive2/ff/723f66745226c8/main.cpp test.cpp
print_file() { export f="$1" ; printf "\n\n========== $1 ==========\n$(cat "$f" | perl -pe 's,(.*),  \1,')" ; }
print_file test.h
print_file test.cpp
print_file main.cpp
g++ -std=c++11 -Wall -pedantic -c main.cpp
g++ -std=c++11 -Wall -pedantic -c test.cpp
g++ main.o test.o
printf "\n\n========== output ==========\n"
./a.out