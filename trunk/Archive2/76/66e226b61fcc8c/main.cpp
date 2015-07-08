#include <iostream>
#include <cstdlib>
 #include <thread>
#include <mutex>

using namespace std;

std::mutex se, so;

void print_sem()
{
    //int ve, vo;
    //sem_getvalue(&se, &ve);
    //sem_getvalue(&so, &vo);
    //cout << "sem_even: " << ve << " sem_odd: " << vo << endl;
}

void even()
{
   int i = 0;
   while (i<=10)
   {
       se.lock();
       print_sem();
       cout << i << endl;
       i+=2;
       so.unlock();
   }
}

void odd()
{
   int i = 1;
   while (i<=9)
   {
       so.lock();
       print_sem();
       cout << i << endl;
       i+=2;
       se.unlock();
   }
}

int main ()
{
    cout << "main() : creating thread - odd" << endl;  
    cout << "main() : creating thread - even" << endl;
    std::thread te (even), to(odd);   
    
    
    //so.lock();
    //cout << "init mutexes" << endl;  
    
    te.join();
    to.join();
   
}