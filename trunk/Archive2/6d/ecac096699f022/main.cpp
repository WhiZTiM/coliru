#include <iostream>
#include <vector>

template <template<typename...> class Template, typename Type>
struct is_template_instance_of {
  static const bool value = false;
};

template <template<typename...> class Template, typename... Args>
struct is_template_instance_of<Template, Template<Args...>> {
  static const bool value = true;
};

int main() {
  std::cout << is_template_instance_of<std::vector, std::vector<int>>::value << std::endl;
  std::cout << is_template_instance_of<std::vector, std::ostream>::value << std::endl;
}
