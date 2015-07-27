#include <mutex>
#include <condition_variable>
#include <queue>
#include <thread>
#include <iostream>

template <typename... Args>
void dump(Args const&... args) {
  static std::mutex stdout_mutex;
  std::lock_guard<std::mutex> guard(stdout_mutex);
  using t = int[];
  (void)t{0, ((void)(std::cerr << args),0)...};
}

template <typename T>
class priority_mutex : std::mutex {
public:
  struct entry {
    entry(T value, std::condition_variable *cv) : value(std::move(value)), cv(cv) {}
    T value;
    std::condition_variable *cv;
    friend bool operator<(entry const& a, entry const& b) { return a.value < b.value; }
  };
  std::priority_queue<entry> queue;
  std::mutex queue_mutex;
  std::mutex work_mutex;

public: 
  void lock(T p) {
    std::unique_lock<std::mutex> guard(queue_mutex);
    std::condition_variable cv;
    queue.emplace(p, &cv);
    std::unique_lock<std::mutex> worker(work_mutex, std::defer_lock);
    cv.wait(guard, [&p, &worker, this]() {
        dump("checking thread with priority ",p,"\n");
        return p == queue.top().value && worker.try_lock();
      });
    queue.pop();
    worker.release();
  }
  void unlock() noexcept {
    work_mutex.unlock();
    std::lock_guard<std::mutex> guard(queue_mutex);
    if (!queue.empty())
      queue.top().cv->notify_one();
  }
};

int main() {  
  priority_mutex<std::size_t> m;
  m.lock(0);
  std::cerr << "Locked main\n";
  std::thread t([&]{m.lock(1); dump("1 t locked!\n"); m.unlock(); dump("1 t unlocked!\n");}),
    u([&]{m.lock(3); dump("3 u locked!\n"); m.unlock(); dump("3 u unlocked!\n");}),
    v([&]{m.lock(2);
        dump("2 v locked!\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // wait for w to start
        m.unlock();
        dump("2 v unlocked!\n");
      });
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  m.unlock();
  dump("Main unlocked!\n");
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  std::thread w([&]{dump("add new lock with priority 4\n"); m.lock(4); dump("4 w locked!\n"); m.unlock(); dump("4 w unlocked!\n");});

  for (auto *tt : {&t, &u, &v, &w})
    tt->join();
}
