#include <string>
#include <unordered_map>
#include <utility>

class A
{};

int main()
{
  std::unordered_map<std::string, std::reference_wrapper<const A>> stringToRef;
  A a;
  stringToRef.insert(std::make_pair("Test", std::cref(a)));
  return 0;
}