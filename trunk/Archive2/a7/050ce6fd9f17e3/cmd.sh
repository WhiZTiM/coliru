set -x
clang++ -O2 -stdlib=libc++ -std=c++03 -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out && g++ -O2 -std=c++03 -Wall -Wextra -pedantic -pthread main.cpp -lcxxrt -ldl && ./a.out