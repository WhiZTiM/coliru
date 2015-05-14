#title Unoptimized atomic vs nonatomic integer increment. (Pointless test, but hey.)
g++ -DATOMIC -std=c++14 -O0 -Wall -pedantic -pthread main.cpp -o atomic
g++ -std=c++14 -O0 -Wall -pedantic -pthread main.cpp -o normal
./atomic
./normal