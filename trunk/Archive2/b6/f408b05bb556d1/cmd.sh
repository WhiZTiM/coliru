set -x; g++ -std=c++03 -O3 -Wall -pedantic -Wextra main.cpp -lboost_iostreams -lz && ./a.out
clang++ -std=c++03 -O3 -Wall -pedantic -Wextra main.cpp -lboost_iostreams -lz && ./a.out
clang++ -stdlib=libc++ -std=c++03 -O3 -Wall -pedantic -Wextra main.cpp -lcxxrt -ldl -lboost_iostreams -lz && ./a.out