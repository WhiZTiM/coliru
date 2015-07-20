clang++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp -lboost_thread -lboost_system -lssl -lcrypto
(for a in {1..5}; do (sleep 1.$RANDOM; echo -e "hello world $RANDOM\\0" | netcat 127.0.0.1 16767)& done)
./a.out | sort | uniq -c | sort -n | tail