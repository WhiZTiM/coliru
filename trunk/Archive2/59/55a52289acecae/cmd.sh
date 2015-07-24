set -x; clang++ -O0 -std=gnu++1y -stdlib=libc++ main.cpp -lcxxrt -ldl -o a && ./a
g++ -O0 -std=gnu++1y  main.cpp -o a && ./a
g++-4.9 -O0 -std=gnu++1y  main.cpp -o a && ./a