set -x;
clang++ -O2 -Wall  -pedantic -DFAULTY main.cpp && ./a.out
clang++ -O2 -Wall -std=c++11 -pedantic -DUSEDELETE main.cpp && ./a.out
clang++ -O2 -Wall  -pedantic -DCPLUSPLUS_03 main.cpp && ./a.out