for v in 0 1
do
    clang++ -std=c++11 -Os -Wall -DDEMO_VERSION=$v main.cpp -o v$v -lboost_system -lboost_serialization
    ./v$v
done