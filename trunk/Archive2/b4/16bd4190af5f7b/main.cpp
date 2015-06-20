#include <type_traits>
#include <iostream>

struct is_base_of_impl
{
    template <typename, typename> static std::false_type 
    sfinae(...);
    template <typename A, typename B> static std::true_type  
    sfinae(decltype(static_cast<A*>(std::declval<B*>())) *);
};

template <typename A, typename B>
struct is_base_of : decltype(is_base_of_impl::sfinae<A, B>(nullptr)) {};

typedef char (&yes)[1];
typedef char (&no)[2];

template <typename B, typename D>
struct Host
{
  operator B*() const;
  operator D*();
};

template <typename B, typename D>
struct is_base_of2
{
  template <typename T> 
  static yes check(D*, T);
  static no check(B*, int);

  static const bool value = sizeof(check(Host<B,D>(), int())) == sizeof(yes);
};

struct A {};
struct B : A {};
struct C : A {};
struct D : B, C {};

int main()
{
    std::cout << is_base_of<A, D>::value << "\n";
    std::cout << is_base_of2<A, D>::value << "\n";
    return 0;
}
