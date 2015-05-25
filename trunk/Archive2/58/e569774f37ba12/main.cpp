#include <mutex>
#include <thread>
#include <iostream>
#include <functional>
#include <condition_variable>

struct data {
  bool has_event;
  int counter;
  std::mutex m;
  std::condition_variable cond;
  data()
  : has_event(false)
  , counter(0)
  {}
};

struct thread1 {
  void operator()(data& obj) const
  {
    std::unique_lock<std::mutex> lock(obj.m);
    obj.has_event = false;
    while (!obj.has_event) {
      obj.cond.wait(lock);
      if (obj.has_event) {
        std::cout << obj.counter << std::endl;
        obj.has_event = false;
      }
    }
  }
};

struct thread2 {
  void operator()(data& obj) const
  {
    for (;;) {
      std::unique_lock<std::mutex> lock(obj.m);
      obj.has_event = true;
      ++obj.counter;
      obj.cond.notify_one();
    }
  }
};

int main()
{
  data obj;
  std::thread t1(thread1(), std::ref(obj));
  std::thread t2(thread2(), std::ref(obj));
  t1.join();
  t2.join();
  
  return 0;
}