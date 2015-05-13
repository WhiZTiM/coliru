echo g++14 && g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo clang++14 && clang++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo g++11 && g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo clang++11 && clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out