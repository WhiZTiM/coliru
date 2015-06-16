#title Strict-aliasing demo
printf "WITHOUT STRICT ALIASING:\n"  ; g++ -std=c++14 -O2 main.cpp -fno-strict-aliasing && ./a.out
printf "\n\nWITH STRICT ALIASING:\n" ; g++ -std=c++14 -O2 main.cpp                      && ./a.out