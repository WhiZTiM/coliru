echo "GCC: " && g++ -std=c++11 -W{all,extra,error} -pedantic-errors main.cpp && ./a.out
echo "===" && echo "Clang: " && clang++ -std=c++11 -W{all,extra,error} -pedantic-errors main.cpp && ./a.out