#include <random>
#include <cstddef>
#include <iostream>
#include <algorithm>
#include <unordered_set>

namespace mystd
{
    
template <typename T, typename H = std::hash<T> >
struct hash
{
    size_t operator()(const T& t) const
    {
        const std::size_t innerHash = H()(t);
        const uint8_t* innerAsHashable = reinterpret_cast<const uint8_t*>(&innerHash);
        
        std::size_t outerHash = _prime;
        
        for (std::size_t i = 0; i < sizeof(std::size_t); i++)
        {
            outerHash ^= innerAsHashable[i];
            outerHash *= _prime;
        }
        
        return outerHash;
    }

    static const std::size_t _prime = 0x01000193;
};

template <typename T>
struct unordered_set : public std::unordered_set<T, ::mystd::hash<T> >
{
    auto pick_random()
    {
        uint8_t* t_as_uint8 = static_cast<uint8_t*>(malloc(sizeof(T)));
        std::default_random_engine generator(std::random_device{}());
        std::uniform_int_distribution<uint8_t> distribution;
        std::generate(t_as_uint8, t_as_uint8 + sizeof(T), [&] () {return distribution(generator); });
        T t = *(reinterpret_cast<T*>(t_as_uint8));
        
        if (this->find(t) != this->end())
        {
            return this->find(t);
        } else {
            this->insert(t);
            auto it = ((++(this->find(t))) != this->end()) ? ++(this->find(t)) : this->begin();
            this->erase(t);
            return it;
        } 
    }
};

}

int main()
{   
    mystd::unordered_set<int> mySet;
    
    for (int i = 0; i < 256; i++) { mySet.insert(i); }

    for (int i = 1; i < 500; i++) {std::cout << *(mySet.pick_random()) << ", ";}

    return 0;
}
