#title tbb concurrent_bounded_queue vs mutex+-protected queue with batch processing
g++ -DATOMIC -std=c++11 -Wall -Wextra -Werror -pedantic -pthread -O2 -ltbb -isystem /usr/include main.cpp -o tbb_queue
g++ -std=c++11 -Wall -Wextra -Werror -pedantic -pthread -O2 main.cpp -o mutex_batch
./tbb_queue ; ./tbb_queue
./mutex_batch ; ./mutex_batch