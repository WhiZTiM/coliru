command() { g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out | sed -e 's,Rob,Grandson,g' | grep -v lol ; } 
declare -f command ; command