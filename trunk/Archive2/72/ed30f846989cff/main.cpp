#include <iostream>
#include <functional>
#include <map>
#include <unordered_map>
#include <tuple>


template <typename T>
class CachedFunction;

template <typename R, typename... Args>
class CachedFunction<R(Args...)>
{
private:
    // Hash function for tuples (needed for unordered_map):
    template <typename Tuple_t, std::size_t Index = std::tuple_size<Tuple_t>::value-1>
    struct TupleHash
    {
        std::size_t operator()(const Tuple_t& tuple) const
        {
            using Element_t = typename std::tuple_element<Index, Tuple_t>::type;
            std::hash<Element_t> hashFunction;
            return TupleHash<Tuple_t, Index-1>()(tuple) ^ hashFunction(std::get<Index>(tuple));
        }    
    };
    
    template <typename Tuple_t>
    struct TupleHash<Tuple_t, 0>
    {
        std::size_t operator()(const Tuple_t& tuple) const
        {
            using Element_t = typename std::tuple_element<0, Tuple_t>::type;
            std::hash<Element_t> hashFunction;
            return hashFunction(std::get<0>(tuple));
        }    
    };
    
public:
    template <typename T>
    CachedFunction(T&& function)
    : _function(std::forward<T>(function))
    {
    }
        
    template <typename... T>
    R operator()(T&&... args)
    {
        auto tuple = std::make_tuple(args...);
        if (_cache.find(tuple) == _cache.end())
        {
            _cache[tuple] = _function(std::forward<T>(args)...);
        }
        return _cache[tuple];
    }
    
private:
    using Tuple_t = decltype(std::make_tuple(std::declval<Args>()...));
    
    std::function<R(Args...)> _function;
    std::unordered_map<Tuple_t, R, TupleHash<Tuple_t>> _cache;
};



int collatz(int n);
int collatz_impl(int n);

int collatz(int n) {
    static CachedFunction<int(int)> collatz_cached = collatz_impl;
    return collatz_cached(n);
}

int collatz_impl(int n) {
    std::cout << n << std::endl;
    if (n == 1) return 0;
    if (n % 2 == 0) return collatz(n/2) + 1;
    return collatz(n*3+1) + 1;
}



int main()
{
    CachedFunction<int(int, int)> cf = [](int i, int j){ std::cout << "!" << std::endl; return i*j; };
    std::cout << cf(1,3) << cf(2,2) << cf(2,2) << cf(1,1) << std::endl;
    
    for (int i = 0; i < 10; ++i) {
        std:: cout << "--- " << i << ": " << collatz(i) << " steps" << std::endl;
    }
}