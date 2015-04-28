#include <iostream>

template <typename R, typename A, typename B>
struct func_signature_holder
{
  typedef R ret_type_t;
  typedef A first_arg_t;
  typedef B second_arg_t;
};

template<typename R, typename A, typename B>
func_signature_holder<R, A, B> just_get_signature( R (*)(A, B) )
{
  return func_signature_holder<R,A,B>();
}

void just_rebuild( int a, double b )
{
  return;
}

int main()
{
    auto res = just_get_signature( &just_rebuild );
    decltype(res)::first_arg_t t = 42;
    decltype(res)::second_arg_t t2 = 10.0;
    t = t + 2;
    t2 = t2 + 2.5;
}
