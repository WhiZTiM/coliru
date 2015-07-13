echo -e "\n\ng++\n"
g++ -std=c++14 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
echo -e "\n\nclang++\n"
clang++ -std=c++14 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out