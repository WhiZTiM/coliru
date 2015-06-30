#include <type_traits>

template<
  typename real_t,
  typename = typename std::enable_if<
    std::is_floating_point<real_t>::value
  >::type
>
struct check_t;

template<
  typename real_t,
  typename = typename
    std::enable_if<
      std::is_floating_point<real_t>::value,
      check_t<real_t>
    >::type
>
class vec_t
{

};

#if 1
template<>
class vec_t<int> {};

template<>
class vec_t<int,check_t<int>> {};
#endif

void test()
{
    vec_t<float> vecf;
    vec_t<int> veci;
}