set -x ; g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out <<< "bf inging /etc/dictionaries-common/words" | grep -v ':-1'