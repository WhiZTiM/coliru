set -x; g++ -std=c++1y -O3 -Wall -pedantic -Wextra main.cpp && ./a.out
clang++ -std=c++1y -O3 -Wall -pedantic -Wextra main.cpp && ./a.out
clang++ -stdlib=libc++ -std=c++1y -O3 -Wall -pedantic -Wextra main.cpp -lcxxrt -ldl && ./a.out