set -x; g++ -std=c++1y -O3 -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out
g++ -std=c++1y -O3 -DSECOND -Wall -pedantic -Wextra main.cpp && ./a.out && stat ./a.out