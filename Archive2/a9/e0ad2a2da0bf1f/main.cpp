#include <functional>
#include <utility>
#include <iostream>
#include <functional>
#include <type_traits>
using namespace std;

//plain function pointers
template<typename... Args, typename ReturnType>
auto make_function(ReturnType(*p)(Args...))
    -> std::function<ReturnType(Args...)> 
{return {p};}

//nonconst member function pointers
template<typename... Args, typename ReturnType, typename ClassType>
auto make_function(ReturnType(ClassType::*p)(Args...)) 
    -> std::function<ReturnType(Args...)>
{return {p};}

//const member function pointers
template<typename... Args, typename ReturnType, typename ClassType>
auto make_function(ReturnType(ClassType::*p)(Args...) const) 
    -> std::function<ReturnType(Args...)>
{return {p};}

//qualified functionoids
template<typename FirstArg, typename... Args, class T>
auto make_function(T&& t) 
    -> std::function<decltype(t(std::declval<FirstArg>(), std::declval<Args>()...))(FirstArg, Args...)> 
{return {std::forward<T>(t)};}

//unqualified functionoids try to deduce the signature of `T::operator()` and use that.
template<class T>
auto make_function(T&& t) 
    -> decltype(make_function(&std::remove_reference<T>::type::operator())) 
{return {std::forward<T>(t)};}


// testing
#include <cassert>
int func(int x, int y, int z) { return x + y + z;}
int overloaded(char x, int y, int z) { return x + y + z;}
int overloaded(int x, int y, int z) { return x + y + z;}
struct functionoid {
    int operator()(int x, int y, int z) { return x + y + z;}
};
struct functionoid_overload {
    int operator()(int x, int y, int z) { return x + y + z;}
    int operator()(char x, int y, int z) { return x + y + z;}
};
int main ()
{
  using namespace std::placeholders;
  int first = 0;
  auto lambda = [](int x, int y, int z) { return x + y + z;};
  auto lambda_state = [=](int x, int y, int z) { return x + y + z + first;};
  auto bound = std::bind(func,_1,_2,_3);
  
  std::function<int(int,int,int)> f0 = make_function(func); assert(f0(1,2,3)==6);
  std::function<int(char,int,int)> f1 = make_function<char,int,int>(overloaded); assert(f1(1,2,3)==6);
  std::function<int(int,int,int)> f2 = make_function<int,int,int>(overloaded); assert(f2(1,2,3)==6);
  std::function<int(int,int,int)> f3 = make_function(lambda); assert(f3(1,2,3)==6);
  std::function<int(int,int,int)> f4 = make_function(lambda_state); assert(f4(1,2,3)==6);
  std::function<int(int,int,int)> f5 = make_function<int,int,int>(bound); assert(f5(1,2,3)==6);
  std::function<int(int,int,int)> f6 = make_function(functionoid{}); assert(f6(1,2,3)==6);
  std::function<int(int,int,int)> f7 = make_function<int,int,int>(functionoid_overload{}); assert(f7(1,2,3)==6);
  std::function<int(char,int,int)> f8 = make_function<char,int,int>(functionoid_overload{}); assert(f8(1,2,3)==6);
  std::cout << "pass";
  
  return 0;
}