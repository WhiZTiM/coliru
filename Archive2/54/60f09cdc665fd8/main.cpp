#include <vector>
#include <iostream>

class Child
{
    public:
    Child() { std::cout << "Constructing Child" << std::endl; }
    Child(const Child & other) { std::cout << "Copy-Constructing Child" << std::endl; }
};

int testPushBack()
{
  std::vector<Child> v;
  Child Item1;
  v.push_back( Item1 );
  return 0;
}

// Okay, so what if getchar was a macro?
//#define getchar getc(stdin)

int main() {
    testPushBack();

	return 0;
}