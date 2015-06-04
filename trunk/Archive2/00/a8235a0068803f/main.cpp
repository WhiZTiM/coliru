#include <thread>
#include <vector>
#include <iostream>
using namespace std;

class worker {
public:
    worker();
    thread mThread;
private:
    void run() { std::cout << "boo\n"; }
};

worker::worker() {
    (this->mThread = thread(&worker::run, this)).detach();
}

class threadpool {
public:
    threadpool(int size);
    void addTask();
private:
    vector<worker> workers;
};

threadpool::threadpool(int size) : workers{size}
{
}

int main()
{
    threadpool tp(20);
}