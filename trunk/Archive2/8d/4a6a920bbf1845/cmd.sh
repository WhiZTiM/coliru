echo -e "\ng++ (libstdc++) ######################################################################"
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out
echo -e "\nclang++ (libc++) ######################################################################"
clang++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp -stdlib=libc++ && ./a.out