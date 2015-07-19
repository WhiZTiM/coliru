#include <iostream>
#include <thread>
#include <mutex>
 
using namespace std;
 
int i = 0;
std::mutex i_mutex;
 
int j = 4;
std::mutex j_mutex;
 
void actOnI() {
    i_mutex.lock();
    for(int x = 0; x < 10; x++) {
        cout << ++i << endl;
    }
    i_mutex.unlock();
}
 
 void actOnJ() {
    j_mutex.lock();
    for(int x = 0; x < 10; x++) {
    	cout << ++j << endl;
    }
    j_mutex.unlock();
}
 
int main()  {
    std::thread iThread1(actOnI);
    std::thread iThread2(actOnI);
    std::thread jThread1(actOnJ);
    std::thread jThread2(actOnJ);
    iThread1.join();
    iThread2.join();
    jThread1.join();
    jThread2.join();
}
