#include <iostream>
#include <string>
#include <vector>
#include <cassert>

// TypeEraser.h

template <std::size_t Tsize, std::size_t Talign>
struct TypeEraser {
public:
    template <class T>
    TypeEraser(T *typeTag);
    
    TypeEraser(TypeEraser &&other);
    
    ~TypeEraser();
    
    TypeEraser(TypeEraser const &) = delete;
    TypeEraser &operator = (TypeEraser const &) = delete;
    
    template <class T>
    T &get();
    
private:
    void (*_deleter)(char *s);
    void (*_mover)(TypeEraser &self, TypeEraser &&other);
    alignas(Talign) char storage[Tsize];
};

template <class Tarchetype>
using TypeEraserFor = TypeEraser<sizeof(Tarchetype), alignof(Tarchetype)>;

template <std::size_t Tsize, std::size_t Talign>
template <class T>
TypeEraser<Tsize, Talign>::TypeEraser(T*)
: _deleter([](char *s) {
    reinterpret_cast<T*>(s)->~T();
})
, _mover([](TypeEraser &self, TypeEraser &&other) {
    new (self.storage) T(std::move(other.get<T>()));
}) {
    static_assert(sizeof(T) == Tsize, "Wrong object size !");
    static_assert(alignof(T) == Talign, "Wrong object alignment !");
    new (storage) T;
}

template <std::size_t Tsize, std::size_t Talign>
template <class T>
T &TypeEraser<Tsize, Talign>::get() {
    #pragma GCC diagnostic ignored "-Wstrict-aliasing"
    return *reinterpret_cast<T*>(storage);
    #pragma GCC diagnostic pop
}

template <std::size_t Tsize, std::size_t Talign>
TypeEraser<Tsize, Talign>::TypeEraser(TypeEraser &&other)
: _deleter(other._deleter)
, _mover(other._mover) {
    _mover(*this, std::move(other));
}


template <std::size_t Tsize, std::size_t Talign>
TypeEraser<Tsize, Talign>::~TypeEraser() {
    _deleter(storage);
}

// MultiVector.h

struct MultiVector {
    template <class T>
    std::vector<T> &all();
    
    template <class T, class... Args>
    T &emplace(Args &&... args);
    
    template <class T>
    T &add(T &&orig);
    
private:
    static std::size_t _tIdCounter;
    
    template <class T>
    static std::size_t typeId();

    std::vector<TypeEraserFor<std::vector<char>>> subVectors;
};

template <class T>
std::size_t MultiVector::typeId() {
    static std::size_t id = _tIdCounter++;
    return id;
}

template <class T>
std::vector<T> &MultiVector::all() {
    std::size_t tId = typeId<T>();
    assert(tId <= subVectors.size());
    if(tId == subVectors.size()) {
        subVectors.emplace_back(static_cast<std::vector<T>*>(nullptr));
    }
    return subVectors[tId].get<std::vector<T>>();
}

template <class T, class... Args>
T &MultiVector::emplace(Args &&... args) {
    auto &allT = all<T>();
    allT.emplace_back(std::forward<Args>(args)...);
    return allT.back();
}

template <class T>
T &MultiVector::add(T &&orig) {
    auto &allT = all<std::remove_reference_t<T>>();
    allT.push_back(std::forward<T>(orig));
    return allT.back();
}

// MultiVector.cpp

std::size_t MultiVector::_tIdCounter = 0u;

int main()
{    
    MultiVector mv;
    
    for(int i = 0; i < 10; ++i)
        mv.add(i);
        
    mv.emplace<std::string>("Hello");
    mv.emplace<std::string>("World");
    mv.emplace<std::string>("!");
    
    for(auto &i : mv.all<int>())
        std::cout << i << ' ';
    std::cout << '\n';
    for(auto &s : mv.all<std::string>())
        std::cout << s << ' ';
    std::cout << '\n';
    
    return 0;
}
