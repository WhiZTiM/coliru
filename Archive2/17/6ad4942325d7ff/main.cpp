#include <type_traits>
typedef void* HSQUIRRELVM;

template<class C, bool UseCallback = false>
  class RefAlloc {
  public:
  template<typename T = void>
  std::enable_if_t<UseCallback, T>
  newCallback(C* p, HSQUIRRELVM vm) { p->setVMContext(vm); }
  
  template<typename T = void>
  std::enable_if_t<!UseCallback, T>
  newCallback(C* p, HSQUIRRELVM vm) { } // nothing, function does not exist
};

int main()
{
  RefAlloc<void> a;
  a.newCallback(nullptr, nullptr);
}
