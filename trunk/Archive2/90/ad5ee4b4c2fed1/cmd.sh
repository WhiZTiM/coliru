set -x; clang++ -O0 -std=gnu++1z -stdlib=libc++ main.cpp -lcxxrt -ldl -o a && ./a
g++ -O0 -std=gnu++1z  main.cpp -lcxxrt -ldl -o a && ./a