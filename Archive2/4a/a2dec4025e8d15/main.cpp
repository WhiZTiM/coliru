#include <vector>
#include <functional>

struct Foo
{
   int tag = 0;
   std::function<void ()> code;
};

int main()
{
   std::vector<Foo> v;
   v.push_back(Foo{ 0, [](){} });
}
