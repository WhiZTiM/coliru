echo -e "\ng++ (libstdc++) ######################################################################"
g++ -v -std=c++1y -O0 -Wall -pedantic -pthread main.cpp && ./a.out
echo -e "\nclang++ (libc++) ######################################################################"
clang++ -v -std=c++14 -O0 -Wall -pedantic -pthread main.cpp && ./a.out