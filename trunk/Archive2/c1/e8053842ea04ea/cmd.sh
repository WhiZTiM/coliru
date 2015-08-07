echo -e "clang++ ##########################################################\n"
clang++ -std=c++14 -O3 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
echo -e "g++ ##########################################################\n"
g++ -std=c++14 -O1 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out;