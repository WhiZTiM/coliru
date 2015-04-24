#include <functional>
#include <memory>

struct NonCopyable {
  void operator()() const {}
  std::unique_ptr<int> ptr_;
};

int main() {
    std::function<void()> f = NonCopyable();
}
