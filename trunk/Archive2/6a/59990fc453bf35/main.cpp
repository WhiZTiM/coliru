#include <iostream>
 
template <typename T>
class StaticVarWrapper
{
  public:
 
  static typename T::Inner_T& get()
  {
      static StaticVarWrapper<T> wrapper;
      return wrapper.var_m;
  }
 
  private:
 
  void init(){}
 
  StaticVarWrapper():
  var_m()
  {
      init();
  }
 
  typename T::Inner_T var_m;
};
 
 
struct StaticNbOfUsers2_st{ typedef int Inner_T; };
typedef StaticVarWrapper<StaticNbOfUsers2_st> StaticNbOfUsers2;
 
template <>
void StaticVarWrapper<StaticNbOfUsers2_st>::init()
{
    var_m = 2;
}
 
struct StaticNbOfUsers3_st{ typedef int Inner_T; };
typedef StaticVarWrapper<StaticNbOfUsers3_st> StaticNbOfUsers3;
 
template <>
void StaticVarWrapper<StaticNbOfUsers3_st>::init()
{
    var_m = 3;
}
 
int main()
{
  int& ref2 = StaticNbOfUsers2::get();
  int& ref3 = StaticNbOfUsers3::get();
 
  std::cout << "ref2 = " << ref2 << std::endl;
  std::cout << "ref3 = " << ref3 << std::endl;
 
  ref2 = ref2*2;
  ref3 = ref3*2;
 
  std::cout << "ref2 = " << ref2 << std::endl;
  std::cout << "ref3 = " << ref3 << std::endl;
 
  return 0;
}