#include <string>
#include <vector>
#include <random>
#include <cstddef>
#include <iostream>
#include <functional>
#include <unordered_set>

template <typename T, typename H = std::hash<T> >
struct Hasher
{
    std::size_t operator()(const T* const pt) const
    {
        return H()(*pt);
    }
};

template <class T, typename H = std::hash<T>> 
struct EqualTo 
{
    bool operator() (const T* x, const T* y) const 
    {
        return Hasher<T, H>()(x) == Hasher<T, H>()(x);
    }
};

template <typename T, typename H = std::hash<T> >
struct PickSet
{
    
    void rebuildAndReserve()
    {
        _unorderedSet.clear();
        _unorderedSet.reserve(_vector.capacity());
        for (const T& t : _vector) _unorderedSet.insert(&t);
    }
    
    void insert(const T& t)
    {
        if (_unorderedSet.find(&t) == _unorderedSet.cend())
        {
            _vector.push_back(t);
            
            if (_unorderedSet.find(&(*(_vector.cbegin()))) != _unorderedSet.cend())
            {
                _unorderedSet.insert(&(*(_vector.crbegin())));
            }
            else
            {
                rebuildAndReserve();
            }
        }
    }
    
    void insert(T&& t)
    {
        const T u(t);
        insert(u);
    }
    
    void erase(const T& t)
    {
        auto fit = _unorderedSet.find(&t);
        
        if (fit != _unorderedSet.end())
        {
            if (*fit != &(*(_vector.crbegin())))
            {
                *(const_cast<T*>(*fit)) = *(_vector.rbegin());
            }
            _vector.pop_back();
        }
    }
    
    void erase(T&& t)
    {
        const T u(t);
        erase(u);
    }

    const T& pickRandom() const
    {
        return _vector[_distribution(_generator) % _vector.size()];
    }
    
    std::unordered_set<const T*, Hasher<T, H>, EqualTo<T, H> > _unorderedSet;
    std::vector<T> _vector;
    
    static std::default_random_engine _generator;
    static std::uniform_int_distribution<std::size_t> _distribution;
};

template <typename T, typename H>
std::default_random_engine PickSet<T, H>::_generator = std::default_random_engine();

template <typename T, typename H>
std::uniform_int_distribution<std::size_t> PickSet<T, H>::_distribution = std::uniform_int_distribution<std::size_t>();

int main()
{
    PickSet<std::string> pickString;
    
    pickString.insert("Hi");
    pickString.insert("this");
    pickString.insert("is");
    pickString.insert("the");
    pickString.insert("C++");
    pickString.insert("Java");
    pickString.insert("spam");
    pickString.insert("Adrien");
    
    pickString.erase("Java");
    
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    std::cout << pickString.pickRandom() << std::endl;
    return 0;
}
