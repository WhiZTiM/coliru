clang++ -std=c++1z -stdlib=libc++ -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded main.cpp -lsupc++ && ./a.out
g++ -std=c++14 -Wall -Wextra main.cpp && ./a.out