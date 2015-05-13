#include<type_traits>
#include<iostream>

template<typename Derived>
struct Base {};

struct Derived : public Base<Derived> {};

struct NotDerived {};

template<typename T, typename U>
struct MultOperation
{
    MultOperation(T const&, U const&) {}
};

template<typename T, typename U>
struct MultOperation<Base<T>, U>
{
    MultOperation(Base<T> const&, U const&) {}
};

template<typename T, typename U>
struct MultOperation<T, Base<U> >
{
    MultOperation(T const&, Base<U> const&) {}
};

template<typename T, typename U>
struct MultOperation<Base<T>, Base<U> >
{
    MultOperation(Base<T> const&, Base<U> const&) {}
};

    template<typename T, typename U>
    struct is_derived_from_base
    {
        static constexpr bool first = std::is_base_of<Base<T>, T>::value;
        static constexpr bool second = std::is_base_of<Base<U>, U>::value;
        
        static constexpr bool none = !first && !second;
        static constexpr bool both = first && second;
        static constexpr bool only_first = first && !second;
        static constexpr bool only_second = !first && second;
    };

    template<typename T, typename U, typename = typename std::enable_if<is_derived_from_base<T,U>::none>::type >
    auto operator*(T const& t, U const& u)
    {
        std::cout<<"Both T and U are not derived"<<std::endl;
        return MultOperation<T, U>(t,u);
    }
    
    
    template<typename T, typename U, typename = typename std::enable_if<is_derived_from_base<T,U>::only_first>::type >
    auto operator*(Base<T> const& t, U const& u)
    {
        std::cout<<"T is derived from Base<T>, U is not derived"<<std::endl;
        return MultOperation<Base<T>, U>(t,u);
    }
    
    template<typename T, typename U, typename = typename std::enable_if<is_derived_from_base<T,U>::only_second>::type >
    auto operator*(T const& t, Base<U> const& u)
    {
        std::cout<<"T is not derived, U is derived from Base<U>"<<std::endl;
        return MultOperation<T, Base<U> >(t,u);
    }
    
    template<typename T, typename U, typename = typename std::enable_if<is_derived_from_base<T,U>::both>::type >
    auto operator*(Base<T> const& t, Base<U> const& u)
    {
        std::cout<<"T is derived from Base<T>, U is derived from Base<U>"<<std::endl;
        return MultOperation<Base<T>, Base<U> >(t,u);
    }


int main()
{
    Derived d;
    NotDerived n;
    auto mult = d*n; (void) mult;   //tha cast to void is just to suppress the warning "unused variable ..."
    auto mult2 = n*d; (void) mult2;
    auto mult3 = d*d; (void) mult3;
    auto mult4 = n*n; (void) mult4;
}

