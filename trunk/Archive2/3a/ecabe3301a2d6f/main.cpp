#include <iostream>
#include <string>
#include <vector>
#include <utility>


class Test {
public:
  Test() = default;
  Test(const Test& m) { std::cout << "copy ctor"; } // Copy constructor
  Test(Test&& m) = delete;
};

int main()
{
   Test obj;
   Test obj2(std::move(obj));
}
