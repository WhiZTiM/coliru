# Semaphore vs Condition variable
g++ -DSEMAPHORE -std=c++11 -O2 -Wall -Wextra -Werror -pedantic -pthread main.cpp -o sema
g++ -std=c++11 -O2 -Wall -Wextra -Werror -pedantic -pthread main.cpp -o cond
./sema
./cond