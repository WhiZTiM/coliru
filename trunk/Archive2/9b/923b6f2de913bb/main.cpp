#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <ctime>
#include <iomanip>

namespace stx
{
    template < typename T, typename A = std::allocator<T>, template <typename,typename> class CNTR = std::vector >
    using stack = std::stack< T, CNTR<T,A> > ;
    
    template < typename T, typename A = std::allocator<T> >
    using terrible_stack = std::stack< T, std::list<T,A> > ;
}

template < typename INT_STACK > long long time_it()
{
    constexpr std::size_t N = 8'000'000 ;

    const auto start = std::clock() ;
    {
        INT_STACK stack ;
        int i = 0 ;
        while( stack.size() < N ) stack.push(++i) ;
        while( stack.size() > N/8 ) stack.pop() ;
        while( stack.size() < N ) stack.push(++i) ;
        while( stack.size() > N/4 ) stack.pop() ;
        while( stack.size() < N ) stack.push(++i) ;
        while( stack.size() > N/2 ) stack.pop() ;
        while( stack.size() < N ) stack.push(++i) ;
    }
    const auto end = std::clock() ;

    return (end-start) * 1000.0 / CLOCKS_PER_SEC ;
}

template < typename INT_STACK > long long time_it_monotonic()
{
    constexpr std::size_t N = 16'000'000 ;

    const auto start = std::clock() ;
    {
        INT_STACK stack ;
        int i = 0 ;
        while( stack.size() < N ) stack.push(++i) ;
        while( !stack.empty() ) stack.pop() ;
    }
    const auto end = std::clock() ;

    return (end-start) * 1000.0 / CLOCKS_PER_SEC ;
}

int main()
{
    std::cout << "typical usage:\n-----------------------\n" ;
    std::cout << std::setw(15) << "stack(deque)" << std::setw(5) << time_it< std::stack<int> >() << " millisecs\n" ;
    std::cout << std::setw(15) << "stack(vector)" << std::setw(5) << time_it< stx::stack<int> >() << " millisecs\n" ;
    std::cout << std::setw(15) << "stack(list)" << std::setw(5) << time_it< stx::terrible_stack<int> >() << " millisecs\n" ;
    
    std::cout << "\nmonotonic usage:\n-----------------------\n" ;
    std::cout << std::setw(15) << "stack(deque)" << std::setw(5) << time_it_monotonic< std::stack<int> >() << " millisecs\n" ;
    std::cout << std::setw(15) << "stack(vector)" << std::setw(5) << time_it_monotonic< stx::stack<int> >() << " millisecs\n" ;
    std::cout << std::setw(15) << "stack(list)" << std::setw(5) << time_it_monotonic< stx::terrible_stack<int> >() << " millisecs\n" ;
}
