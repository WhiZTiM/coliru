echo -e "\ng++ (libstdc++) ######################################################################"
g++-4.9 -v -std=c++1y -O0 -Wall -pedantic -pthread main.cpp && ./a.out
echo -e "\nclang++ (libc++) ######################################################################"
clang++ -std=c++14 -O0 -Wall -pedantic -pthread main.cpp -stdlib=libc++ && ./a.out