echo -e "\ng++ ##########################################\n"
g++ -std=c++14 -Wall -pedantic main.cpp && ./a.out
echo -e "\nclang++ ##########################################\n"
clang++ -std=c++14 -Wall -pedantic main.cpp && ./a.out