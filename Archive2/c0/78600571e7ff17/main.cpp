#include <iostream>
#include <string>
#include <stdint.h>
#include <cassert>
#include <limits>
#include <map>
#include <vector>
#include <algorithm>
#include <experimental/any>
#include <type_traits>

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
    std::experimental::any value;
    AttrType type;

public:
    // Constructors
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
    AttrValue(List& value) : value(value), type(AttrType::LIST) {}
    AttrValue(InitList&& value) : value(List(std::move(value))), type(AttrType::LIST) {}

    AttrValue(const Dictionary& value) : value(value), type(AttrType::DICTIONARY) {}
    AttrValue(Dictionary&& value) : value(value), type(AttrType::DICTIONARY) {}
    AttrValue(DictInitList&& value) : value(Dictionary(std::move(value))), type(AttrType::DICTIONARY) {}
    
    template <typename T> AttrValue(T) = delete;
    
    // Castings
    #define CASTING_FUNC(__TYPE__, __ATTR_TYPE__)            \
    operator __TYPE__() const                                \
    {                                                        \
        assert(type == __ATTR_TYPE__);                       \
        return std::experimental::any_cast<__TYPE__>(value); \
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
            return std::experimental::any_cast<double>(value);
        }
        return std::experimental::any_cast<float>(value);
    }
    
    operator long long() const
    {
        assert(type == AttrType::INT64 || type == AttrType::INT);
        if (type == AttrType::INT64)
        {
            return std::experimental::any_cast<long long>(value);
        }
        return std::experimental::any_cast<int>(value);
    }
    
    operator long() const
    {
        assert(type == AttrTypeLONG || type == AttrType::INT);
        if (type == AttrTypeLONG)
        {
            return std::experimental::any_cast<LongEquivalent_t>(value);
        }
        return std::experimental::any_cast<int>(value);
    }
    
    CASTING_FUNC(List, AttrType::LIST);
    CASTING_FUNC(Dictionary, AttrType::DICTIONARY);
    
    template <typename T>
    operator std::vector<T>() const
    {
        assert(type == AttrType::LIST);
        List list = std::experimental::any_cast<List>(value);
        std::vector<T> vectorResult;
        vectorResult.reserve(list.size());
        std::transform(list.begin(), list.end(), std::back_inserter(vectorResult), [](AttrValue& attrValue){ return (T)attrValue; });
        return vectorResult;
    }
    
    template <typename T>
    operator std::map<std::string, T>() const
    {
        assert(type == AttrType::LIST);
        Dictionary dictionary = std::experimental::any_cast<Dictionary>(value);
        std::map<std::string, T> mapResult;
        std::transform(dictionary.begin(), dictionary.end(), std::inserter(mapResult, mapResult.end()), [](AttrValue& attrValue){ return (T)attrValue; });
        return mapResult;
    }
    
    template <typename T> operator T() const = delete;
    
    //List
    List asList()
    {
        assert(type == AttrType::LIST);
        return std::experimental::any_cast<List>(value);
    }
    
    //Dictionary
    Dictionary asDictionary()
    {
        assert(type == AttrType::DICTIONARY);
        return std::experimental::any_cast<Dictionary>(value);
    }
};


int main()
{
    AttrValue attrVec = {3, 2, 1, 10};
    std::vector<int> vec = attrVec;
    
    int i = vec.at(2);
    std::cout << i << std::endl;
}