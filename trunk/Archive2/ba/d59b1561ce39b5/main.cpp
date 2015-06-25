#include <memory>
#include <functional>

template<typename T>
using noop_unique_ptr = std::unique_ptr<T, std::function<void(T*)>>;

int main(int argc, char **argv) {
  noop_unique_ptr<int> ptr = std::make_unique<int>(666);
}