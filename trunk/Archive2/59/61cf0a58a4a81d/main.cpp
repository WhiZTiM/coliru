#include <iostream>
#include <string>
using namespace std;

template<template <class> class MF>
   struct static_visitor
   {
      template<class T>
         auto operator()(const T& t) -> decltype((t.*MF<T>{}())())
         {
            return (t.*MF<T>{}())();
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

template <template <class> class MF, class T>
   auto apply_visit(static_visitor<MF> v, T obj) -> decltype(v(obj))
   {
      return v(obj);
   }

template <class T>
   struct name_
   {
      auto operator()() const -> decltype(&T::name)
      {
         return &T::name;
      }
   };

int main()
{
   static_visitor<name_> v; // <-- add indirection here?
   cout << apply_visit(v, Person{}) << '\n';
   cout << apply_visit(v, Critter{}) << endl;
}