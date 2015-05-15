#include <type_traits>
using namespace std;

class Base{};

class Derived : public Base{};

class NotDerived{};

template <typename T, typename Enable = void>
class SomeClass;

template <typename T>
struct DerivedFromBase : conditional_t<is_base_of<Base, T>::value, true_type, false_type>{};

template <typename T, typename Enable = void>
class A;

template <typename T>
class A<T, enable_if_t<DerivedFromBase<T>::value> >
{
};

template <typename T>
enable_if_t<is_base_of<Base, T>::value> CallOnlyIfDerivedFromBase()
{
}

int main() 
{
 A<Derived> a;
 CallOnlyIfDerivedFromBase<Derived>();
 //A<NotDerived> b;
 CallOnlyIfDerivedFromBase<NotDerived>();
 return 0;
}