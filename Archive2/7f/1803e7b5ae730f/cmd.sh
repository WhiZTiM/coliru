# Semaphore vs Condition variable
g++ -DSEMAPHORE -std=c++11 -O2 -ggdb -Wall -Wextra -Werror -pedantic -pthread main.cpp -isystem /opt/local/include -o sema
g++ -std=c++11 -O2 -ggdb -Wall -Wextra -Werror -pedantic -pthread main.cpp -isystem /opt/local/include -o cond
./sema
./cond