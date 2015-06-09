#include <iostream>
#include <string>
#include <stdint.h>
#include <cassert>
#include <limits>
#include <map>
#include <vector>
#include <experimental/any>
#include <type_traits>

template <bool b> struct longEquivalent;
template <> struct longEquivalent<true> { using type = int; };
template <> struct longEquivalent<false> { using type = long long; };
using longEquivalent_t = longEquivalent<sizeof(int) == sizeof(long)>::type;

class AttrValue
{
    using List = std::vector<AttrValue>;
    using Dictionary = std::map<std::string, AttrValue>;
    using InitList = std::initializer_list<AttrValue>;
    using DictInitList = std::initializer_list<Dictionary::value_type>;
    
public:
    // AttrType
    enum class AttrType { UNKNOWN = 0, BOOL, INT, INT64, FLOAT, DOUBLE, STRING, LIST, DICTIONARY };
    static constexpr AttrType AttrTypeLONG = sizeof(int) == sizeof(long) ? AttrType::INT : AttrType::INT64;
    
    // Internal data
    std::experimental::any value;
    AttrType type;
    
    // Constructors
    AttrValue(int value) : value(value), type(AttrType::INT) {}
    AttrValue(long value) : value(value), type(AttrTypeLONG) {}
    AttrValue(bool value) : value(value), type(AttrType::BOOL) {}
    AttrValue(float value) : value(value), type(AttrType::FLOAT) {}
    AttrValue(double value) : value(value), type(AttrType::DOUBLE) {}
    AttrValue(long long value) : value(value), type(AttrType::INT64) {}
    
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
    #define CASTING_FUNC(__TYPE__, __UNDERLYING_TYPE__, __ATTR_TYPE__)  \
    operator __TYPE__()                                                 \
    {                                                                   \
        assert(type == __ATTR_TYPE__);                                  \
        return std::experimental::any_cast<__UNDERLYING_TYPE__>(value); \
    }
        
    CASTING_FUNC(int, int, AttrType::INT);
    CASTING_FUNC(long, longEquivalent_t, AttrTypeLONG);
    CASTING_FUNC(bool, bool, AttrType::BOOL);
    CASTING_FUNC(float, float, AttrType::FLOAT);
    CASTING_FUNC(double, double, AttrType::DOUBLE);
    CASTING_FUNC(long long, long long, AttrType::INT64);
    CASTING_FUNC(std::string, std::string, AttrType::STRING);
    CASTING_FUNC(List, List, AttrType::LIST);
    CASTING_FUNC(Dictionary, Dictionary, AttrType::DICTIONARY);
    
    template <typename T> operator T() = delete;
    
    //List
    List asList() {
        assert(type == AttrType::LIST);
        return std::experimental::any_cast<List>(value);
    }
    
    //Dictionary
    Dictionary asDictionary() {
        assert(type == AttrType::DICTIONARY);
        return std::experimental::any_cast<Dictionary>(value);
    }
};


int main()
{
    std::vector<AttrValue> vec = {"hola", 2};
    AttrValue val = vec;
    AttrValue val2 = val;
    std::string x = val2.asList().at(0);
    val2 = 2;
    int y = val2;
    std::cout << x << y << std::endl;
    
    AttrValue val3 = 3LL;
    std::int64_t c = val3;
    std::cout << c << std::endl;
}