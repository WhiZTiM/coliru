set -x; time g++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread main.cpp && ./a.out
time clang++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread -lcxxrt -ldl main.cpp && ./a.out
time clang++ -stdlib=libc++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread -lcxxrt -ldl main.cpp && ./a.out