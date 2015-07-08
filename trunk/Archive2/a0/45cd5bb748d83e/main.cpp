#include <iostream>
#include <cstdlib>
 #include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

class Semaphore {
public:
    Semaphore (int count_ = 0)
        : count(count) {if (count>0) cv.notify_all();}

    inline void notify()
    {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }

    inline void wait()
    {
        std::unique_lock<std::mutex> lock(mtx);

        while(count == 0){
            cv.wait(lock);
        }
        count--;
    }

private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};

Semaphore se (1), so(0);

void even()
{
   int i = 0;
   while (i<=10)
   {
       se.wait();
       cout << i << endl;
       i+=2;
       so.notify();
   }
}

void odd()
{
   int i = 1;
   while (i<=9)
   {
       so.wait();
       cout << i << endl;
       i+=2;
       se.notify();
   }
}

int main ()
{
    cout << "main() : creating thread - odd" << endl;  
    cout << "main() : creating thread - even" << endl;
    std::thread te (even), to(odd);    
    se.notify();
    te.join();
    to.join();
   cout << "finish" << endl;
}