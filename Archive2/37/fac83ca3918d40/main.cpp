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
    CachedFunction()
    : _function(nullptr)
    {
    }
    
    CachedFunction(const CachedFunction& other)
    : _function(other._function)
    {
    }
    
    CachedFunction(CachedFunction&& other) noexcept
    : _function(std::move(other._function))
    {
    }
    
    template <typename T, typename = typename std::enable_if<!std::is_same<typename std::remove_const<typename std::remove_reference<T>::type>::type, CachedFunction>::value>::type>
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


int main()
{
    CachedFunction<int(int)> cf1 = [](int i){ std::cout << "cf1" << std::endl; return i*i; };
    cf1(10);
    cf1(10);
    
    const CachedFunction<int(int)> cf2 = cf1;
    //cf2(20);
    //cf2(20);
    
    CachedFunction<int(int)> cf3 = cf2;
    cf3(30);
    cf3(30);

    CachedFunction<int(int)> cf4 = std::move(cf2);
    cf3(40);
    cf3(40);
}