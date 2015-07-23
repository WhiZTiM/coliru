#include <iostream>
#include <string>
using namespace std;

template <class E>
   struct static_visitor_
   {
      E extractor;
      static_visitor_(E extractor) : extractor{extractor}
         { }
      template <class T>
         auto operator()(const T &obj) const -> decltype(extractor(obj))
         {
            return extractor(obj);
         }
      template <class T>
         auto operator()(T &obj) const -> decltype(extractor(obj))
         {
            return extractor(obj);
         }
   };

template <class E>
   static_visitor_<E> static_visitor(E extractor)
   {
       return static_visitor_<E>{extractor};
   }

struct Person
{
   string name() const { return "Jens"; }
};
struct Critter
{
   string name() const { return "Patrice"; }
};

struct get_name_extractor
{
    template <class T>
        string operator()(const T &arg) const
        {
            return arg.name();
        }
};

int main()
{
   auto v = static_visitor(get_name_extractor{});
   cout << v(Person{}) << '\n' << v(Critter{}) << endl;
}