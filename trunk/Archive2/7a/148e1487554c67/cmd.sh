clang -std=c++1y -O3 -pedantic -lstdc++ main.cpp -lboost_system && ./a.out |& c++filt -t