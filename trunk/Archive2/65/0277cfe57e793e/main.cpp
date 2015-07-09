#include <initializer_list>
#include <utility>

template<typename Return, typename T>
T ReceiveFuncPtr (Return (T::*Method)(const int&))
{
  T obj;  // Found and declared an object of actual container class
  (obj.*Method)(1);  // Some processing
  return obj;  // Returned that container class object with RVO
} 

template<typename T, typename T2 = void>
struct MySet
{
  std::pair<T,bool> insert (const T& i) { return std::pair<T,bool>(T(),true); }
  std::pair<T,bool> insert (T&& i) { return std::pair<T,bool>(T(),true); }
  void insert (std::initializer_list<T> i) { }
  template <class U>
  void insert(U u1, U u2) {}
};

int main ()
{
  ReceiveFuncPtr(&MySet<int>::insert);  // OK
}