#include <mutex>

class two_priority_mutex {
  std::mutex low_priority_mutex, next_access_mutex, data_mutex;
public:
  void lock() {
    std::unique_lock<std::mutex> low(low_priority_mutex);
    std::lock_guard<std::mutex> guard(next_access_mutex);
    data_mutex.lock();
    low.release();
  }
  void unlock() noexcept {
    data_mutex.unlock();
    low_priority_mutex.unlock();
  }
  void high_priority_lock() {
      std::lock_guard<std::mutex> guard(next_access_mutex);
      data_mutex.lock();
  }
  void high_priority_unlock() {
      data_mutex.unlock();
  }
  class high {
    two_priority_mutex *me;
  public:
    high(two_priority_mutex *me) : me(me) {}
    void lock() { me->high_priority_lock(); }
    void unlock() { me->high_priority_unlock(); }
  };
  high high_priority_locker() {
    return high(this);
  }
};

#include <iostream>
#include <thread>

template <typename... Args>
void dump(Args const&... args) {
  static std::mutex stdout_mutex;
  std::lock_guard<std::mutex> guard(stdout_mutex);
  using t = int[];
  (void)t{0, ((void)(std::cerr << args),0)...};
}

int main()
{
  two_priority_mutex m;
  
  auto p1 = [&m]{
    for (int i=0; i<20; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      dump("1? ask for high priority lock\n");
      auto h = m.high_priority_locker();
      std::lock_guard<two_priority_mutex::high> g(h);
      dump("1! got high priority lock\n");
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
  };
  auto p2 = [&m]{
    for (int i=0; i<10; ++i) {
      std::lock_guard<two_priority_mutex> g(m);
      dump("2  got low priority lock\n");
      std::this_thread::sleep_for(std::chrono::milliseconds(123));
    }
  };
  std::thread t(p1), u(p2), v(p2), w(p2);
  for (auto *tt : {&t, &u, &v, &w}) tt->join();
}
