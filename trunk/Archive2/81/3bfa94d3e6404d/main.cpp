#include <functional>

template <typename T, typename Comparer = std::greater<T>>
class LinkedList
{
  //...
  void insert(T& value)
  {
      Comparer comp;
      //...
      if ( comp(value, current_item) ) // tests if value > current_item
  };