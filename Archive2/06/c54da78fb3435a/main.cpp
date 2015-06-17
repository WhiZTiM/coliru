#include <iostream>
#include <stdint.h>
#include <cassert>
#include <limits>
#include <algorithm>
//#include <experimental/any>
#include <type_traits>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>


class Anything
{
private:
    struct Base {
        virtual ~Base() = default;
        virtual Base* clone() const = 0;
    };

    template<typename T>
    struct Derived : Base
    {
        T value;
        
        template<typename U>
        Derived(U&& value) : value(std::forward<U>(value)) {}
        
        Base* clone() const { return new Derived<T>(value); }
    };
    
    Base* ptr;
    
public:
    Anything() : ptr(nullptr) { std::cout << "Anything()" << std::endl; }
    
    ~Anything()
    {
        std::cout << "~Anything()" << std::endl;
        if (ptr) delete ptr;
    }
    
    Anything(const Anything& rhs) : ptr(rhs.ptr ? rhs.ptr->clone() : nullptr) { std::cout << "Anything(const Anything& rhs)" << std::endl; }
    Anything(Anything&& rhs) : ptr(rhs.ptr) { rhs.ptr = nullptr; std::cout << "Anything(Anything&& rhs)" << std::endl; }
    
    Anything& operator=(const Anything& rhs) {
        std::cout << "operator=(const Anything& rhs)" << std::endl;
        ptr = rhs.ptr ? rhs.ptr->clone() : nullptr;
        return *this;
    }
    
    Anything& operator=(Anything&& rhs)
    {
        std::cout << "operator=(Anything&& rhs)" << std::endl;
        ptr = rhs.ptr;
        rhs.ptr = nullptr; 
        return *this;
    }
    
    template <typename T, typename = typename std::enable_if<!std::is_same<typename std::decay<T>::type, Anything>::value>::type>
    Anything(T&& value) : ptr(new Derived<T>(std::forward<T>(value))) { std::cout << "Anything(T&& value)" << std::endl; }
    
    template <typename T, typename = typename std::enable_if<!std::is_same<typename std::decay<T>::type, Anything>::value>::type>
    Anything& operator=(T&& value)
    {
        std::cout << "Anything& operator=(T&& value)" << std::endl;
        ptr = new Derived<T>(std::forward<T>(value));
        return *this;
    }
    
    template <typename T>
    T as() const
    {
        std::cout << "anything.as<T>()" << std::endl;
        assert(dynamic_cast<Derived<T>*>(ptr) != nullptr);
        return static_cast<Derived<T>*>(ptr)->value;
    }
};

template <typename T>
T anything_cast(const Anything& anything)
{
    std::cout << "anything_cast(const Anything& anything)" << std::endl;
    return anything.as<T>();
}


template <bool b> struct LongEquivalent;
template <> struct LongEquivalent<true> { using type = int; };
template <> struct LongEquivalent<false> { using type = long long; };
using LongEquivalent_t = LongEquivalent<sizeof(int) == sizeof(long)>::type;

class AttrValue
{
public:
//private:
    using List = std::vector<AttrValue>;
    using Dictionary = std::map<std::string, AttrValue>;
    using InitList = std::initializer_list<AttrValue>;
    using DictInitList = std::initializer_list<Dictionary::value_type>;
    
public:
    // AttrType
    enum class AttrType { UNKNOWN = 0, BOOL, INT, INT64, FLOAT, DOUBLE, STRING, LIST, DICTIONARY };
    
    static std::string attrTypeToString(AttrType type)
    {
        switch(type) {
            case AttrType::UNKNOWN: return "UNKNOWN";
            case AttrType::BOOL: return "BOOL";
            case AttrType::INT: return "INT";
            case AttrType::INT64: return "INT64";
            case AttrType::FLOAT: return "FLOAT";
            case AttrType::DOUBLE: return "DOUBLE";
            case AttrType::STRING: return "STRING";
            case AttrType::LIST: return "LIST";
            case AttrType::DICTIONARY: return "DICTIONARY";
        }
        assert(false);
        return "ERROR";
    }
    
//private:
    static constexpr AttrType AttrTypeLONG = sizeof(int) == sizeof(long) ? AttrType::INT : AttrType::INT64;
    
    // Internal data
    Anything value;
    AttrType type;

public:
    // Constructors
    AttrValue() : value(), type(AttrType::UNKNOWN) {}
    
    AttrValue(int value) : value(value), type(AttrType::INT) {}
    AttrValue(bool value) : value(value), type(AttrType::BOOL) {}
    AttrValue(float value) : value(value), type(AttrType::FLOAT) {}
    AttrValue(double value) : value(value), type(AttrType::DOUBLE) {}
    AttrValue(long long value) : value(value), type(AttrType::INT64) {}
    AttrValue(long value) : value(LongEquivalent_t(value)), type(AttrTypeLONG) {}
    
    AttrValue(const std::string& value) : value(value), type(AttrType::STRING) {}
    AttrValue(std::string&& value) : value(std::move(value)), type(AttrType::STRING) {}
    AttrValue(const char* value) : value(std::string(value)), type(AttrType::STRING) {}
    
    AttrValue(const List& value) : value(value), type(AttrType::LIST) {}
    AttrValue(List&& value) : value(std::move(value)), type(AttrType::LIST) {}
    AttrValue(InitList&& value) : value(List(std::move(value))), type(AttrType::LIST) {}
    template <typename T> AttrValue(const std::set<T>& set) : value(List(set.begin(), set.end())), type(AttrType::LIST) {}
    template <typename T> AttrValue(const std::list<T>& list) : value(List(list.begin(), list.end())), type(AttrType::LIST) {}
    template <typename T> AttrValue(const std::deque<T>& deque) : value(List(deque.begin(), deque.end())), type(AttrType::LIST) {}
    template <typename T> AttrValue(const std::vector<T>& vector) : value(List(vector.begin(), vector.end())), type(AttrType::LIST) {}
    template <typename T> AttrValue(const std::multiset<T>& multiset) : value(List(multiset.begin(), multiset.end())), type(AttrType::LIST) {}
    
    AttrValue(const Dictionary& value) : value(value), type(AttrType::DICTIONARY) {}
    AttrValue(Dictionary&& value) : value(std::move(value)), type(AttrType::DICTIONARY) {}
    AttrValue(DictInitList&& value) : value(Dictionary(std::move(value))), type(AttrType::DICTIONARY) {}
    template <typename T> AttrValue(const std::map<std::string, T>& map) : value(Dictionary(map.begin(), map.end())), type(AttrType::DICTIONARY) {}
    template <typename T> AttrValue(const std::unordered_map<std::string, T>& unorderedMap) : value(Dictionary(unorderedMap.begin(), unorderedMap.end())), type(AttrType::DICTIONARY) {}
    
    template <typename T> AttrValue(T) = delete;
    
    // Castings
    #define CASTING_FUNC(__TYPE__, __ATTR_TYPE__)   \
    operator __TYPE__() const                       \
    {                                               \
        assert(type == __ATTR_TYPE__);              \
        return anything_cast<__TYPE__>(value);      \
    }
        
    CASTING_FUNC(int, AttrType::INT);
    CASTING_FUNC(bool, AttrType::BOOL);
    CASTING_FUNC(float, AttrType::FLOAT);
    CASTING_FUNC(std::string, AttrType::STRING);
    
    operator double() const
    {
        assert(type == AttrType::DOUBLE || type == AttrType::FLOAT);
        if (type == AttrType::DOUBLE)
        {
            return anything_cast<double>(value);
        }
        return anything_cast<float>(value);
    }
    
    operator long long() const
    {
        assert(type == AttrType::INT64 || type == AttrType::INT);
        if (type == AttrType::INT64)
        {
            return anything_cast<long long>(value);
        }
        return anything_cast<int>(value);
    }
    
    operator long() const
    {
        assert(type == AttrTypeLONG || type == AttrType::INT);
        if (type == AttrTypeLONG)
        {
            return anything_cast<LongEquivalent_t>(value);
        }
        return anything_cast<int>(value);
    }
    
    CASTING_FUNC(List, AttrType::LIST);
    CASTING_FUNC(Dictionary, AttrType::DICTIONARY);
    
    template <typename T>
    operator std::vector<T>() const
    {
        std::cout << "!" << std::endl;
        assert(type == AttrType::LIST);
        List list = anything_cast<List>(value);
        std::vector<T> vectorResult;
        vectorResult.reserve(list.size());
        std::cout << "!" << std::endl;
        std::transform(list.begin(), list.end(), std::back_inserter(vectorResult), [](const AttrValue& attrValue){ return (T)attrValue; });
        return vectorResult;
    }
    
    template <typename T>
    operator std::map<std::string, T>() const
    {
        assert(type == AttrType::LIST);
        Dictionary dictionary = anything_cast<Dictionary>(value);
        std::map<std::string, T> mapResult;
        std::transform(dictionary.begin(), dictionary.end(), std::inserter(mapResult, mapResult.end()), [](const AttrValue& attrValue){ return (T)attrValue; });
        return mapResult;
    }
    
    template <typename T> operator T() const = delete;
    
    //List
    List asList()
    {
        assert(type == AttrType::LIST);
        return anything_cast<List>(value);
    }
    
    //Dictionary
    Dictionary asDictionary()
    {
        assert(type == AttrType::DICTIONARY);
        return anything_cast<Dictionary>(value);
    }
};

int main()
{
    AttrValue attrVect;
    std::vector<int> vect = {1,2,3};
    attrVect = vect;
    std::vector<int> vect2 = attrVect;
    std::map<std::string, int> map = {{"a", 1}, {"b", 2}};
    attrVect = {};
    std::cout << AttrValue::attrTypeToString(attrVect.type) << std::endl;
    int i = vect.at(2);
    std::cout << i << std::endl;
    Anything a;
    Anything b;
    a = b;
}