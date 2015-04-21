#title Partial demultiplexing using priority_queue
export num_packets=1000
clang++ -DNUM_PACKETS=${num_packets} -std=c++14 -stdlib=libc++ -O2 -Wall -pedantic -pthread main.cpp && ./a.out >packets
head -n${num_packets} packets >a; tail -n${num_packets} packets >b; paste -d '	' a b | head -n100