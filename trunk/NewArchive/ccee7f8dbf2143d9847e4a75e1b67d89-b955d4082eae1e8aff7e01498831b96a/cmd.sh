g++ -std=c++11 -O2 -pthread main.cpp && ./a.out ; function print() { echo "$1" && bash -c "$1" ; } ; print 'cat foo.hpp' ; print 'cat foo.cpp' ; print 'cat test.cpp' ; print 'g++ foo.cpp test.cpp -o app && ./app'