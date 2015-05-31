set -x; for LS in 50 100
do 
time g++ -DLIST_SIZE=$LS -std=c++1y -O2 -Wall -Wextra -pedantic main.cpp
time g++ -DLIST_SIZE=$LS -DUSE_INDEXER -std=c++1y -O2 -Wall -Wextra -pedantic main.cpp
done