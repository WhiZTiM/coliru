#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <forward_list>
#include <random>
#include <vector>

template <typename T>
struct mallocator {
  using value_type = T;

  mallocator() = default;
  template <class U>
  mallocator(const mallocator<U>&) {}

  T* allocate(std::size_t n) {
    std::cout << "allocate(" << n << ")\n";
    return (T*)std::malloc(n * sizeof(T));
  }
  void deallocate(T* ptr, std::size_t n) {
    std::cout << "deallocate(" << ptr << ", " << n << ")\n";
    std::free(ptr);
  }
};

template <typename T, typename U>
inline bool operator == (const mallocator<T>&, const mallocator<U>&) {
  return true;
}

template <typename T, typename U>
inline bool operator != (const mallocator<T>& a, const mallocator<U>& b) {
  return !(a == b);
}

int main() {
    auto engine = std::mt19937_64{std::random_device{}()};
    auto dist = std::uniform_int_distribution<int>{};
    auto rng = [&]{return dist(engine);};

    {
        // vector.
        auto c = std::vector<int, my_allocator<int>>{};
        std::generate_n(std::back_inserter(c), 1024, rng);
    }

    {
        // forward_list
        auto c = std::forward_list<int, my_allocator<int>>{};
        std::generate_n(std::front_inserter(c), 1024, rng);
    }
}