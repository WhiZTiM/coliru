g++ -std=c++14 -DUGLY_LOOP  -O3 -Wall -pedantic -pthread main.cpp -o ugly_loop
g++ -std=c++14 -DCLEAN_LOOP -O3 -Wall -pedantic -pthread main.cpp -o clean_loop
{ for i in {1..4} ; do ./clean_loop 1; done ; for i in {1..4} ; do ./ugly_loop 2  ; done ; } | column -t