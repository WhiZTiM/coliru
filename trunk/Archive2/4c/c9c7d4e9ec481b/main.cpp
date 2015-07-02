#include <type_traits>

template<typename T,typename U>
struct copy_cv_reference
{
private:
    using R = std::remove_reference_t<T>;
    using U1 = std::conditional_t<std::is_const<R>::value, std::add_const_t<U>, U>;
    using U2 = std::conditional_t<std::is_volatile<R>::value, std::add_volatile_t<U1>, U1>;
    using U3 = std::conditional_t<std::is_lvalue_reference<T>::value, std::add_lvalue_reference_t<U2>, U2>;
    using U4 = std::conditional_t<std::is_rvalue_reference<T>::value, std::add_rvalue_reference_t<U3>, U3>;
public:
    using type = U4;
};

template<typename T,typename U>
using copy_cv_reference_t = typename copy_cv_reference<T,U>::type;

struct A;
struct B;

static_assert(std::is_same< copy_cv_reference_t<          A         , B >,          B          >{}, "");
static_assert(std::is_same< copy_cv_reference_t<          A const   , B >,          B const    >{}, "");
static_assert(std::is_same< copy_cv_reference_t< volatile A         , B >, volatile B          >{}, "");
static_assert(std::is_same< copy_cv_reference_t< volatile A const   , B >, volatile B const    >{}, "");
static_assert(std::is_same< copy_cv_reference_t<          A        &, B >,          B        & >{}, "");
static_assert(std::is_same< copy_cv_reference_t<          A const  &, B >,          B const  & >{}, "");
static_assert(std::is_same< copy_cv_reference_t< volatile A        &, B >, volatile B        & >{}, "");
static_assert(std::is_same< copy_cv_reference_t< volatile A const  &, B >, volatile B const  & >{}, "");
static_assert(std::is_same< copy_cv_reference_t<          A       &&, B >,          B       && >{}, "");
static_assert(std::is_same< copy_cv_reference_t<          A const &&, B >,          B const && >{}, "");
static_assert(std::is_same< copy_cv_reference_t< volatile A       &&, B >, volatile B       && >{}, "");
static_assert(std::is_same< copy_cv_reference_t< volatile A const &&, B >, volatile B const && >{}, "");

int main()
{
}
