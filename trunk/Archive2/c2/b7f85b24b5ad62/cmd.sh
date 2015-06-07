echo -e "\n\ng++ libstdc++ ######################################################################################################\n"
g++ -std=c++14 -O0 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp && ./a.out
echo -e "\n\nclang++ libc++ ######################################################################################################\n"
clang++ -std=c++14 -O0 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp -stdlib=libc++ && ./a.out