#include <iostream>
#include <stdint.h>
#include <cassert>
#include <limits>
#include <algorithm>
#include <type_traits>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
//#include <experimental/any>


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
        Derived(U&& value) : value(std::forward<U>(value))
        {
        }
        
        Base* clone() const
        {
            return new Derived<T>(value);
        }
    };
    
    Base* ptr;
    
public:
    template <typename T>
    using StorageType = typename std::decay<T>::type;

    Anything()
    : ptr(nullptr)
    {
    }
    
    ~Anything()
    {
        delete ptr;
    }
    
    Anything(const Anything& rhs)
    : ptr(rhs.ptr ? rhs.ptr->clone() : nullptr)
    {
    }
    
    Anything(Anything&& rhs) : ptr(rhs.ptr)
    {
        rhs.ptr = nullptr;
    }
    
    Anything& operator=(const Anything& rhs)
    {
        ptr = rhs.ptr ? rhs.ptr->clone() : nullptr;
        return *this;
    }
    
    Anything& operator=(Anything&& rhs)
    {
        ptr = rhs.ptr;
        rhs.ptr = nullptr; 
        return *this;
    }
    
    template <typename T, typename = typename std::enable_if<!std::is_same<typename std::decay<T>::type, Anything>::value>::type>
    Anything(T&& value)
    : ptr(new Derived<StorageType<T>>(std::forward<T>(value)))
    {
    }
    
    template <typename T, typename = typename std::enable_if<!std::is_same<typename std::decay<T>::type, Anything>::value>::type>
    Anything& operator=(T&& value)
    {
        ptr = new Derived<StorageType<T>>(std::forward<T>(value));
        return *this;
    }
    
    template <typename T>
    StorageType<T> as() const
    {
        assert(dynamic_cast<Derived<StorageType<T>>*>(ptr) != nullptr);
        return static_cast<Derived<StorageType<T>>*>(ptr)->value;
    }
};

template <typename T>
T anything_cast(const Anything& anything)
{
    return anything.as<T>();
}



template <bool b> struct LongEquivalent;
template <> struct LongEquivalent<true> { using type = int; };
template <> struct LongEquivalent<false> { using type = long long; };
using LongEquivalent_t = LongEquivalent<sizeof(int) == sizeof(long)>::type;

class AttrValue
{
private:
    using List = std::vector<AttrValue>;
    using Dictionary = std::map<std::string, AttrValue>;
    using InitList = std::initializer_list<AttrValue>;
    using DictInitList = std::initializer_list<Dictionary::value_type>;
    
public:
    // AttrType
    enum class AttrType { UNKNOWN = 0, BOOL, INT, INT64, FLOAT, DOUBLE, STRING, LIST, DICTIONARY };
    
private:
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
        assert(type == AttrType::LIST);
        List list = anything_cast<List>(value);
        std::vector<T> vectorResult;
        vectorResult.reserve(list.size());
        std::transform(list.begin(), list.end(), std::back_inserter(vectorResult), [](const AttrValue& attrValue){ return (T)attrValue; });
        return vectorResult;
    }
    
    template <typename T>
    operator std::map<std::string, T>() const
    {
        assert(type == AttrType::DICTIONARY);
        Dictionary dictionary = anything_cast<Dictionary>(value);
        std::map<std::string, T> mapResult;
        std::transform(dictionary.begin(), dictionary.end(), std::inserter(mapResult, mapResult.end()), [](const std::pair<std::string, AttrValue>& pair){ return std::make_pair(pair.first, (T)pair.second); });
        return mapResult;
    }
    
    template <typename T> operator T() const = delete;
    
    // To string
    std::string to_string() const
    {
        switch(type)
        {
            case AttrType::UNKNOWN:
                return "NULL";
            case AttrType::BOOL:
                return std::to_string(anything_cast<bool>(value));
            case AttrType::INT:
                return std::to_string(anything_cast<int>(value));
            case AttrType::INT64:
                return std::to_string(anything_cast<long long>(value));
            case AttrType::FLOAT:
                return std::to_string(anything_cast<float>(value));
            case AttrType::DOUBLE:
                return std::to_string(anything_cast<double>(value));
            case AttrType::STRING:
                return '"' + anything_cast<std::string>(value) + '"';
            case AttrType::LIST:
            {
                List list = anything_cast<List>(value);
                std::string str = "[";
                str += std::accumulate(list.begin(), list.end(), std::string(), [](const std::string& accumulated, const AttrValue& attrValue) {
                    std::string strValue = attrValue.to_string();
                    return accumulated.empty() ? strValue : accumulated + ',' + strValue;
                });
                str += ']';
                return str;
            }
            case AttrType::DICTIONARY:
            {
                Dictionary dictionary = anything_cast<Dictionary>(value);
                std::string str = "{";
                str += std::accumulate(dictionary.begin(), dictionary.end(), std::string(), [](const std::string& accumulated, const std::pair<std::string, AttrValue>& pair) {
                    std::string strValue = '"' + pair.first + '"' + ':' + pair.second.to_string();
                    return accumulated.empty() ? strValue : accumulated + ',' + strValue;
                });
                str += '}';
                return str;
            }
        }
        return "NULL";
    }
    
    // Convenience functions: Maybe they are not needed and should be removed
    
    // List
    List asList()
    {
        assert(type == AttrType::LIST);
        return anything_cast<List>(value);
    }
    
    // Dictionary
    Dictionary asDictionary()
    {
        assert(type == AttrType::DICTIONARY);
        return anything_cast<Dictionary>(value);
    }
};



// Test functions
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& container)
{
    os << "std::vector[";
    if (!container.empty()) os << (*container.cbegin());
    for (auto it = ++container.cbegin(); it != container.cend(); ++it) os << ',' << (*it);
    os << ']';
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::map<K,V>& container)
{
    os << "std::map{";
    if (!container.empty()) os << (*container.cbegin());
    for (auto it = ++container.cbegin(); it != container.cend(); ++it) os << ',' << (*it);
    os << '}';
    return os;
}

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<K,V>& pair)
{
    os << pair.first << ':' << pair.second;
    return os;
}



int main()
{
    std::vector<int> vect = {1,2,3};
    AttrValue attrVect = vect;
    std::cout << vect << ' ' << attrVect.to_string() << std::endl;
    
    std::map<std::string, int> map = {{"a", 1}, {"b", 2}};
    AttrValue attrMap = map;
    std::cout << map << ' ' << attrMap.to_string() << std::endl;
    
    AttrValue attrTest = {map, 1, 2.0, "hola", attrVect, AttrValue()};
    std::cout << attrTest.to_string() << std::endl;
}