#include <cstddef>
#include <atomic>


/// A class that lazily binds a unique (for each implementation of Atom)
/// identifier to a thread.  This is a fallback mechanism for the access
/// spreader if we are in testing (using DeterministicAtomic) or if
/// __vdso_getcpu can't be dynamically loaded
struct SequentialThreadId {

  /// Returns the thread id assigned to the current thread
  static size_t get() {
    auto rv = currentId;
    if (rv == 0) {
      rv = currentId = ++prevId;
    }
    return rv;
  }

  /// Fills the thread id into the cpu and node out params (if they
  /// are non-null).  This method is intended to act like getcpu when a
  /// fast-enough form of getcpu isn't available or isn't desired
  static int getcpu(unsigned* cpu, unsigned* node, void* unused) {
    auto id = get();
    if (cpu) {
      *cpu = id;
    }
    if (node) {
      *node = id;
    }
    return 0;
  }

 private:
  static std::atomic<size_t> prevId;

  static __thread size_t currentId;
};


std::atomic<size_t> SequentialThreadId::prevId;
size_t __thread SequentialThreadId::currentId;



#include <iostream>
#include <thread>


int main()
{
    enum { num_cpu = 16 };
    for (auto i = 0; i != 100; ++i)
    {
        std::thread([]{
            std::cout << SequentialThreadId::get() % num_cpu << ' ';
        }).join();
    }
}