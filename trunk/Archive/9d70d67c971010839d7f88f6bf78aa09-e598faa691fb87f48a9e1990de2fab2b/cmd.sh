for i in `seq 6 8` ; do CMD="g++-4.$i -std=c++0x -O2 -pthread main.cpp" && echo $CMD && $CMD && ./a.out ; printf "\n\n" ; done