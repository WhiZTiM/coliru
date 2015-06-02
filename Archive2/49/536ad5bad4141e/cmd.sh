echo -e "\n\ng++ -O0 ######################################################################################################\n"
g++ -std=c++14 -O0 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp -S && cat main.s
echo -e "\n\ng++ -O3 ######################################################################################################\n"
g++ -std=c++14 -O3 -Wall -Wextra -pedantic -Wno-unused-variable -Wno-unused-parameter -pthread main.cpp -S && cat main.s