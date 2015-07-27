#include <string>

template <typename R, typename... Params>
constexpr bool is_noexcept(R(*p)(Params...)) {
    return noexcept(p(std::declval<Params>()...));
}


void strProcessor(const std::string& str) noexcept(true) { }

struct Type{
  void method1() noexcept(is_noexcept(strProcessor)) {
     strProcessor("");
  }
};

int main() {}
