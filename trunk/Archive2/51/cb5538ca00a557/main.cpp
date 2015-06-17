#include <memory>

struct S {
  int i;
  
  S() : i(0) {}
  S(int i) : i(i) {}
  S(const S&) = default;
  S& operator=(const S&) = default;
};

int main() {
  // Get some temporary memory.
  S *vals = std::get_temporary_buffer<S>(5).first;
  
  std::return_temporary_buffer(vals);
}
