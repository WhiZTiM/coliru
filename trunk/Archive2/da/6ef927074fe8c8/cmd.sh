#title demultiplexing using priority_queue
set +x
export num_packets=1000
clang++ -Dnum_packets=${num_packets} -std=c++14 -stdlib=libc++ -O2 -Wall -pedantic -pthread main.cpp && ./a.out >packets
printf "Left column shows packets ordered by receive time. Right column shows the result of partial demultiplexing with priority_queue. (Grouping by port number enables batch processing later on):\n"
head -n${num_packets} packets >a; tail -n${num_packets} packets >b; paste -d '	' a b