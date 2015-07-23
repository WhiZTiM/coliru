#include <iostream>
#include <string>
using namespace std;

template <class R>
   struct static_visitor
   {
      template <class T>
         R operator()(const T &obj) const
         {
            return obj.name();
         }
   };

struct Person
{
   string name() const { return "Jens"; }
};
struct Critter
{
   string name() const { return "Patrice"; }
};

int main()
{
   static_visitor<string> v;
   cout << v(Person{}) << '\n' << v(Critter{}) << endl;
}