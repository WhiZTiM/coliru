#include <iostream>
#include <utility>

struct check
{
   template <typename T>
   decltype(std::declval<T>().value, void()) foo()
   {
      std::cout << "The type has a value member.\n";
   }
   
   template <typename T>
   auto foo() -> decltype(std::declval<T>(), void())
   {
      std::cout << "The type does not have a value member.\n";
   }
} var;

int main()
{
   struct apple
   {
      int value{};
   };
   
   struct grape{};

   var.foo<apple>();
   //var.foo<grape>();
}