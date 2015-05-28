echo -e "\ng++ (libstdc++, no optimizations) ######################################################################"
g++ -std=c++11 -O0 -Wall -pedantic -pthread main.cpp && ./a.out
echo -e "\ng++ (libstdc++, -O3) ######################################################################"
g++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp && ./a.out