set -x; g++ -std=c++03 -O3 -Wall -pedantic -Wextra main.cpp && ./a.out
clang++ -std=c++03 -O3 -Wall -pedantic -Wextra main.cpp && ./a.out
clang++ -stdlib=libc++ -std=c++03 -O3 -Wall -pedantic -Wextra main.cpp -lcxxrt -ldl && ./a.out