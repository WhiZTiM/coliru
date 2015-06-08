#include <vector>
#include <functional>

struct Foo
{
   std::function<void ()> code;
};

int main()
{
   
   std::vector<Foo> w = {  { [](){} }  } ;
}

