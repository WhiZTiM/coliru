ln -sfv /Archive2/8f/ea1d0bb536489a/main.cpp vector_patch.hpp
clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -lboost_system -lboost_serialization && ./a.out