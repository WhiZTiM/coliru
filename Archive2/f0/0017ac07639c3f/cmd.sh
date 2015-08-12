#title flat_set vs set (benchmark)
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp -DFLAT_SET=1 -o flat_set
g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp -DFLAT_SET=0 -o std_set
{ echo "flat_set: $(./flat_set)" ; echo "std_set: $(./std_set)" ; } | column -t