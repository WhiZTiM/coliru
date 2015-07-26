echo -e "\n\nclang++ no optimizations ####################################################\n"
clang++ -std=c++14 -O0 -Wall -Wextra -pedantic main.cpp -S -o -
echo -e "\n\nclang++ optimized ####################################################\n"
clang++ -std=c++14 -O3 -Wall -Wextra -pedantic main.cpp -S -o -