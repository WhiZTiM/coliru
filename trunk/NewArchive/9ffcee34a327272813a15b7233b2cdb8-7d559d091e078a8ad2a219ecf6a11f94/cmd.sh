ln -s /Archive/1a969c08e38def870e19bb9c817bb1b0-d41d8cd98f00b204e9800998ecf8427e/main.cpp a.cpp
ln -s /Archive/7bc79174ca06883cf62dc5d8ffaedc52-f674c1a6d04c632b71a62362c0ccfc51/main.cpp a.h
g++ -c -std=c++11 -O2 -Wall -pedantic -pthread main.cpp
g++ -c -std=c++11 -O2 -Wall -pedantic -pthread a.cpp
g++ *.o
./a.out