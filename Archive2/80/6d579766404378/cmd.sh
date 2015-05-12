g++ -fPIC -fsplit-stack -c main.cpp
g++ -shared -o libmain.so main.o