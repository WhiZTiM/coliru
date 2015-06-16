printf "WITHOUT STRICT ALIASING:\n"  ; g++ -std=c++14 -O2 main.cpp -fno-strict-aliasing && ./a.out
printf "\n\nWITH STRICT ALIASING:\n" ; g++ -std=c++11 -O2 main.cpp                      && ./a.out