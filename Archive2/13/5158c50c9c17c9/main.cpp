#include <iostream>
#include <functional>
#include <map>

//http://stackoverflow.com/questions/20834838/using-tuple-in-unordered-map

template <typename T>
class CachedFunction;

template <typename R, typename... Args>
class CachedFunction<R(Args...)>
{
private:
    template <typename T, typename... TArgs>
    std::size_t hash(T value, TArgs... args)
    {
        return hash(value) ^ hash(args...);
    }
    
    template <typename T>
    std::size_t hash(T value)
    {
        std::hash<T> hash_fn;
        return hash_fn(value);
    }

public:
    template <typename T>
    CachedFunction(T&& function)
    : _function(std::forward<T>(function))
    {
    }
        
    template <typename... T>
    R operator()(T&&... args)
    {
        std::size_t hash_value = hash(args...);
        if (_cache.find(hash_value) == _cache.end())
        {
            _cache[hash_value] = _function(std::forward<T>(args)...);
        }
        return _cache[hash_value];
    }
    
private:
    std::function<R(Args...)> _function;
    std::map<std::size_t, R> _cache;
};

int main()
{
    CachedFunction<int(int, int)> cf = [](int i, int j){ std::cout << "!" << std::endl; return i*j; };
    std::cout << cf(1,3) << cf(2,2) << cf(2,2) << std::endl;
}