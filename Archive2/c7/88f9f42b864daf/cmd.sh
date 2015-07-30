#title Adapt struct rpc
g++ -std=c++14 -c -Wall -pedantic -pthread main.cpp -E -o - | perl -pe 's,{,{\n,g; s,},}\n,g; s,;,;\n,g'