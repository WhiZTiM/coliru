set -x; g++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread -lboost_system main.cpp && ./a.out
clang++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread -lcxxrt -ldl -lboost_system main.cpp && ./a.out
clang++ -stdlib=libc++ -std=c++1y -O2 -Wall -Wextra -pedantic -pthread -lcxxrt -ldl -lboost_system  main.cpp && ./a.out