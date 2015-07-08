#include <iostream>
#include <cstdlib>
 #include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

std::mutex me, mo;
std::condition_variable cve, cvo;

void even()
{
   int i = 0;
   while (i<=10)
   {
       std::unique_lock<std::mutex> lock(me);
       cve.wait(lock);
       cout << i << endl;
       i+=2;
       cvo.notify_one();
   }
}

void odd()
{
   int i = 1;
   while (i<=9)
   {
       std::unique_lock<std::mutex> lock(mo);
       cvo.wait(lock);
       cout << i << endl;
       i+=2;
       cve.notify_one();
   }
}

int main ()
{
    cout << "main() : creating thread - odd" << endl;  
    cout << "main() : creating thread - even" << endl;
    std::thread te (even), to(odd);    
    cve.notify_one();
    te.join();
    to.join();
   cout << "finish" << endl;
}