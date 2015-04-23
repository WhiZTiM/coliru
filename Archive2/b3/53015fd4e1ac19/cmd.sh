g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp ; gzip - <a.out | base64 >clipboard
# on your (Linux) machine:
base64 -d <clipboard | gunzip - >b.out ; chmod 755 b.out ; ./b.out && echo "Et voila!"