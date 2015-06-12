set -x; g++ -std=c++11 -O3 -Wall -pedantic -Wextra main.cpp -lboost_iostreams -lz && ./a.out; echo ========================================
clang++ -std=c++11 -O3 -Wall -pedantic -Wextra main.cpp -lboost_iostreams -lz && ./a.out; echo ========================================
clang++ -stdlib=libc++ -std=c++11 -O3 -Wall -pedantic -Wextra main.cpp -lcxxrt -ldl -lboost_iostreams -lz && ./a.out