#include <type_traits>

namespace
{
template<class T>
struct mut_
{
    T& value;
    
    operator T&() { return value; }
    operator T const&() const { return value; }
    
    T& get() { return value; }
    T const& get() const { return value; }
};
}

template<class T>
struct mut_pre
{
    T& value;
    
    mut_<T> operator&() { return mut_<T>{value}; }
};

template<class T, std::enable_if_t<!std::is_const<T>::value, int> = 0>
struct mut_pre<T> mut(T& v){ return mut_pre<T>{v}; }

//////

void f(mut_<int> v){}

int main()
{
    int i = 42;
    f(&mut(i));
}