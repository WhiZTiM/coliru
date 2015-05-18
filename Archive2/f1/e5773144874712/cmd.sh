echo -e "\ng++ (libstdc++) ######################################################################"
g++ -std=c++1y -O0 -Wall -pedantic -pthread main.cpp && ./a.out
echo -e "\ng++ (libstdc++, -fno-elide-constructors) ######################################################################"
g++ -std=c++1y -O0 -Wall -pedantic -pthread -fno-elide-constructors main.cpp && ./a.out
echo -e "\nclang++ (libc++) ######################################################################"
clang++ -std=c++14 -O0 -Wall -pedantic -pthread main.cpp && ./a.out