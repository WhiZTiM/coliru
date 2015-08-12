#include <memory>
#include <vector>
#include <string>
#include <iostream>
#include <scoped_allocator>

struct SomeStruct
{
   template <typename T>
   using Allocator = std::allocator<T>;

   template <typename T>
   using ScopedAllocator = std::scoped_allocator_adaptor<Allocator<T>>;

   using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;

   template <typename T>
   using Vector = std::vector<T, ScopedAllocator<T>>;

   SomeStruct()
   :  s{allocator},
      v(ScopedAllocator<String>{allocator})
   {
   }

   std::allocator<char> allocator;
   String s;
   Vector<String> v;
};


int main(int argc, char* argv[])
{
    SomeStruct ss;

    std::cout << "faffing with vector\n";
    ss.v.push_back("hello");  // *** This fails to compile.
    std::cout << ss.v[0] << "\n";

return 0;
}