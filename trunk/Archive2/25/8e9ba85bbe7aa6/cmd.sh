echo '----- without library ------' && g++-4.8 -std=c++11 -O2 -Wall -Wextra -pedantic-errors -pthread main.cpp && ./a.out
echo '------ with library --------' && g++-4.8 -std=c++11 -O2 -Wall -Wextra -pedantic-errors -pthread main.cpp -lboost_date_time && ./a.out