echo -e "\ng++ (libstdc++) ######################################################################"
g++ -std=c++11 -O3 -Wall -pedantic -pthread main.cpp && ./a.out
echo -e "\nclang++ (libc++) ######################################################################"
#clang++ -std=c++14 -O3 -Wall -pedantic -pthread main.cpp