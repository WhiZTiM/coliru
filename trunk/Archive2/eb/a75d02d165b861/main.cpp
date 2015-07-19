#include <iostream>
#include <thread>
#include <atomic>
#include <string>
 
using namespace std;
 
atomic_int i{0};
atomic_int j{4};
 
void actOnI(const string& threadName) {
    for(int x = 0; x < 3; x++) {
        cout << threadName << ": " << i.fetch_add(1) << endl;
    }
}
 
 void actOnJ(const string& threadName) {
    for(int x = 0; x < 3; x++) {
        cout << threadName << "j: " << j.fetch_add(1) << endl;
    }
}
 
int main()  {
    std::thread iThread1(actOnI, "iThread1");
    std::thread iThread2(actOnI, "iThread2");
    std::thread jThread1(actOnJ, "jThread1");
    std::thread jThread2(actOnJ, "jThread2");
    iThread1.join();
    iThread2.join();
    jThread1.join();
    jThread2.join();
}