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
            std::size_t seed = TupleHash<Tuple_t, Index-1>()(tuple);
            std::size_t hash_value = hashFunction(std::get<Index>(tuple));
            return seed ^ (hash_value + 0x9e3779b9 + (seed << 6) + (seed >> 2)); // Inspired on boost.hash_combine.
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
        std::cout << "0" << std::endl;
    }
    
    CachedFunction(CachedFunction& cachedFunction)
    : _function(cachedFunction._function)
    {
        std::cout << "1" << std::endl;
    }
    
    CachedFunction(CachedFunction&& cachedFunction)
    : _function(std::move(cachedFunction._function))
    {
        std::cout << "2" << std::endl;
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
    
    void clear()
    {
        _cache.clear();
    }
    
private:
    static_assert(!std::is_same<R, void>::value, "the result_type of the CachedFunction can not be void");
    using Tuple_t = decltype(std::make_tuple(std::declval<Args>()...));
    
    std::function<R(Args...)> _function;
    std::unordered_map<Tuple_t, R, TupleHash<Tuple_t>> _cache;
};


std::size_t fibonacci_impl(int n);

std::size_t fibonacci(int n)
{
    static CachedFunction<std::size_t(int)> fibonacci_cached = fibonacci_impl;
    return fibonacci_cached(n);
}

std::size_t fibonacci_impl(int n)
{
    //std::cout << n << std::endl;
    if (n < 2) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}


int main()
{
    std::cout << "0:" << std::endl;
    CachedFunction<int(int)> cf1([](int i){ std::cout << i << std::endl; return i*i; });
    cf1(5);
    //cf1(5);
    
    std::cout << "1:" << std::endl;
    CachedFunction<int(int)> cf2 = cf1;
    cf2(5);
    //cf2(5);
    
    
    std::cout << "2:" << std::endl;
    CachedFunction<int(int)> cf3 = std::move(cf1);
    cf3(5);
    //cf3(5);
    
    /*
    for (int i = 0; i < 92; ++i)
    {
        std:: cout << "fibonacci(" << i << "): " << fibonacci(i) << std::endl;
    }
    */
}