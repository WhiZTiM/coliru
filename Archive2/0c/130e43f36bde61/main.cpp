#include <cstdlib>
#include <iostream>
#include <atomic>
#include <cstddef>
#include <thread>
#include <stdio.h>
#include <unistd.h>

#define capacity 1000
 

 
std::atomic<int> _head;
std::atomic<int> _tail;
 
int array[capacity];
 
int increment(int size)
{
    return (size+1)%capacity;
}
 
// avoid pointerss unless you absolutely need them. copying is often cheaper
bool push(int item)
{
    printf("Inside push; %d\n", item);
    const int current_tail= _tail.load(std::memory_order_relaxed);
    const int next_tail=increment(current_tail);
 
    if(next_tail != _head.load(std::memory_order_acquire))
    {
         array[current_tail]=item;
         _tail.store(next_tail,std::memory_order_release);
 
         return true;
    }
 
         return false; //Queue is Full
}

 // avoid pointerss unless you absolutely need them
bool pop(int* item)
{
      printf("Inside pop\n");
      const int current_head=_head.load(std::memory_order_relaxed);
 
      if(current_head==_tail.load(std::memory_order_acquire))
      {
          return false;//empty queue
      }
 
      *item=array[current_head];
      _head.store(increment(current_head),std::memory_order_release);
 
      return true;
}
 
bool isEmpty()
{
    return(_head.load()==_tail.load());
}
 
bool isFull()
{
    const int next_tail=increment(_tail);
 
    return (next_tail==_head.load());
}
 
bool isLockfree()
{
    return (_tail.is_lock_free() && _head.is_lock_free());
}
 
void threadfunction_push()
{
    int item = 0;
 
    for(item=0;item<10000;item++)
    {
        while(false == push(item)) {
           std::this_thread::yield();
        }
        printf("pushed %d into queue\n",item);
        //usleep(100);
     }
}
 
void threadfunction_pop()
{
    
    int item = 0;
    for(int i=0;i<10000;i++)
    {
       while(false == pop(&item)) {
             std::this_thread::yield();
       }
       
       printf("popped %d from queue\n",item);

    }
}
 

int main(int argc, char** argv)
{
     auto i=isLockfree();
     if(i)
        printf("Queue is lock Free\n");
     else 
        printf("Queue is NOT lock Free\n");
        

    std::thread thread_push(threadfunction_push);
    std::thread thread_pop(threadfunction_pop);
 
    thread_push.join();
    thread_pop.join();
 
     return 0;
}