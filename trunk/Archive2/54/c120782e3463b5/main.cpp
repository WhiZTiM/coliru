#include <random>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <map>
#include <algorithm>
#include <memory>

class Anything
{
private:
    struct AnythingBase {
        virtual ~AnythingBase() = default;
    };

    template<typename T>
    struct AnythingDerived : AnythingBase
    {
        T value;
        
        template<typename U>
        AnythingDerived(U&& value) : value(std::forward<U>(value)) {}
    };
    
    std::unique_ptr<AnythingBase> ptr;
    
public:
    Anything() : ptr(nullptr) { std::cout << "Anything()" << std::endl; }
    
    Anything(Anything& rhs) = delete;
    Anything(const Anything& rhs) = delete;
    
    Anything(Anything&& rhs) : ptr(std::move(rhs.ptr)) { std::cout << "Anything(Anything&& rhs)" << std::endl; }
    
    template <typename T>
    Anything(T&& value) : ptr(std::make_unique<AnythingDerived<T>>(std::forward<T>(value))) { std::cout << "Anything(T&& value)" << "" << std::endl; }
    
    Anything& operator=(Anything& rhs) = delete;
    Anything& operator=(const Anything& rhs) = delete;
    
    Anything& operator=(Anything&& rhs)
    {
        std::cout << "operator=(Anything&& rhs)" << std::endl;
        ptr = std::move(rhs.ptr);
        return *this;
    }
    
    template <typename T>
    Anything& operator=(T&& value)
    {
        std::cout << "Anything& operator=(T&& value)" << "" << std::endl;
        ptr = std::make_unique<AnythingDerived<T>>(std::forward<T>(value));
        return *this;
    }
    
    template <typename T>
    T& value()
    {
        return static_cast<AnythingDerived<T>*>(ptr)->value;
    }
};

class AttrValue : public Anything
{
private:
    using List = std::vector<AttrValue>;
    using Dict = std::map<std::string, AttrValue>;
    using InitList = std::initializer_list<AttrValue>;
    using DictInitList = std::initializer_list<Dict::value_type>;
    
    enum class Type : char { INTEGER, FLOAT, DOUBLE, STRING, LIST, DICCIONARY };
    
    static constexpr Type type_of(int) { return Type::INTEGER; }
    static constexpr Type type_of(float) { return Type::FLOAT; }
    static constexpr Type type_of(double) { return Type::DOUBLE; }
    static constexpr Type type_of(const std::string&) { return Type::STRING; }
    static constexpr Type type_of(const List&) { return Type::LIST; }
    static constexpr Type type_of(const Dict&) { return Type::DICCIONARY; }
    
    Type type;

public:
    template <typename T>
    AttrValue(T&& value) : Anything(std::forward<T>(value)), type(type_of(value)) {}
    
    AttrValue(const char* value) : Anything(std::string(value)), type(Type::STRING) {}
    
    AttrValue(const InitList& value) : Anything(List(value)), type(Type::LIST) {}
    AttrValue(InitList&& value) : Anything(List(std::move(value))), type(Type::LIST) {}
    
    AttrValue(const DictInitList& value) : Anything(Dict(value)), type(Type::DICCIONARY) {}
    AttrValue(DictInitList&& value) : Anything(Dict(std::move(value))), type(Type::DICCIONARY) {}
};

int main()
{
    Anything anything = 1;
    Anything anyOther= 2;
    anyOther = std::move(anything);
    anyOther = 1;
    
    AttrValue v = std::string("hola");
}