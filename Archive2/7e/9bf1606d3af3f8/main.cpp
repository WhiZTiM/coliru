#include <iostream>
#include <functional>
#include <unordered_map>
#include <map>
#include <utility>
//http://stackoverflow.com/questions/20834838/using-tuple-in-unordered-map

template <typename T>
class CachedFunction;

template <typename R, typename... Args>
class CachedFunction<R(Args...)>
{
private:
    template <typename Tuple, size_t Index = std::tuple_size<Tuple>::value-1>
    struct tuple_hash
    {
        std::size_t operator()(const Tuple& tuple) const
        {
            std::cout << Index << std::endl;
            using Element_type = typename std::tuple_element<Index, Tuple>::type;
            std::hash<Element_type> hash_fn;
            return tuple_hash<Tuple,Index-1>()(tuple) ^ hash_fn(std::get<Index>(tuple));
        }
    };
    
    template <typename Tuple>
    struct tuple_hash<Tuple, 0>
    {
        std::size_t operator()(const Tuple& tuple) const
        {
            std::cout << 0 << std::endl;
            using Element_type = typename std::tuple_element<0, Tuple>::type;
            std::hash<Element_type> hash_fn;
            return hash_fn(std::get<0>(tuple));
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
    using Tuple_type = decltype(std::make_tuple(std::declval<Args>()...));
    
    std::function<R(Args...)> _function;
    std::unordered_map<Tuple_type, R, tuple_hash<Tuple_type>> _cache;
};

int main()
{
    CachedFunction<int(int, int)> cf = [](int i, int j){ std::cout << "!" << std::endl; return i*j; };
    std::cout << cf(1,3) << cf(2,2) << cf(2,2) << std::endl;
}