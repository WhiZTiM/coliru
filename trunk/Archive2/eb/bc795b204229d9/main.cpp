#include<set>
template<typename Return, typename T>
T ReceiveFuncPtr (Return (T::*Method)(const int&))
{
  T obj;  // Found and declared an object of actual container class
  (obj.*Method)(1);  // Some processing
  return obj;  // Returned that container class object with RVO
} 
int main ()
{
  ReceiveFuncPtr(&std::set<int>::insert); // ERROR
}