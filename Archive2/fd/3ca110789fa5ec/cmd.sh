clang++ -std=c++11 -O3 -pedantic main.cpp -mtune=native -march=native -S && clang++ --version && cat main.s |grep asm_marker -C4