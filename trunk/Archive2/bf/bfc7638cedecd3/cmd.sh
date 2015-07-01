#title mutex.lock() vs while (!mutex.try_lock()) and latency
echo "Locking: " ; g++ -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out && ./a.out && ./a.out
echo "Spinning: " ; g++ -DSPINLOCK -std=c++14 -O2 -Wall -pedantic -pthread main.cpp && ./a.out && ./a.out && ./a.out
echo "(Don't trust Coliru results. Test on a real machine.)"