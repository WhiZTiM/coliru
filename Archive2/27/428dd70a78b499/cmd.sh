echo -e "g++ & libstdc++ ######################################################################################################\n"
g++ -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp && ./a.out
echo -e "clang++ & libc++ ######################################################################################################\n"
clang++ -std=c++11 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -Wconversion -pthread main.cpp -stdlib=libc++ && ./a.out