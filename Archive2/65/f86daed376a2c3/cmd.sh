clang++ -std=c++1y -Weverything -Wno-c++98-c++11-compat-pedantic main.cpp; echo "34.8 33.5 32.9 30.5 33.3 31.9 30.6 34.4 36.2 35.2 33.2 31.0 31.8 34.4 33.0 32.9 32.8 31.9 31.6 32.2 29.5 36.8 30.9 30.2 35.3 32.1 31.2 36.0 38.2 34.2 34.5 34.7 33.2 39.4 31.2 28.6" > file.txt; ./a.out <<< "file.txt"