#include<algorithm>
#include<iostream>
#include<array>

template<typename T, typename ... Args>
struct in_impl
{
    in_impl(T const& t, Args const& ... args) : val({t, args ...}) {}

    std::array<T, sizeof ...(Args) + 1> val;
};


template<typename T, typename ... Args>
bool operator==(T const& t, in_impl<T, Args ...> const& in)
{
    return std::find(std::begin(in.val), std::end(in.val), t) != std::end(in.val);
}


template<typename T, typename ... Args>
auto in(T const& t, Args const& ... args)
{
    return in_impl<T, Args ...>(t, args ...);
}


int main()
{
    if(1 == in(1,2,3) )
    {
        std::cout<<"1 is in"<<std::endl;
    }
}
    