g++ --version -std=c++1y -O3 -pedantic -lstdc++ main.cpp -lboost_regex && ./a.out |& c++filt -t