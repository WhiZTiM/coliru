#include <iostream>
#include <string>
#include <stdint.h>
#include <cassert>
#include <limits>
#include <map>
#include <vector>
#include <experimental/any>


struct is64bits
{
    static const bool value = sizeof(long) == sizeof(long long);
};


class AttrValue
{
    using List = std::vector<AttrValue>;
    using Dictionary = std::map<std::string, AttrValue>;
    using InitList = std::initializer_list<AttrValue>;
    using DictInitList = std::initializer_list<Dictionary::value_type>;
    
public:
    enum class AttrType { UNKNOWN, BOOL, INT, INT64, FLOAT, DOUBLE, STRING, LIST, DICTIONARY };
    
    AttrType typeOf(bool) { return AttrType::BOOL; }
    AttrType typeOf(int) { return AttrType::INT; }
    AttrType typeOf(long) { if (is64bits::value) { return AttrType::INT64; } return AttrType::INT; }
    AttrType typeOf(long long) { return AttrType::INT64; }
    AttrType typeOf(float) { return AttrType::FLOAT; }
    AttrType typeOf(double) { return AttrType::DOUBLE; }
    AttrType typeOf(std::string) { return AttrType::STRING; }
    AttrType typeOf(List) { return AttrType::LIST; }
    AttrType typeOf(Dictionary) { return AttrType::DICTIONARY; }
    //AttrType typeOf(char) { return AttrType::UNKNOWN; } //WHY MUST THIS BE ADDED?
    AttrType typeOf(...) { return AttrType::UNKNOWN; }
    
    static std::string type_to_string(AttrType type)
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
    
    //Internal data
    std::experimental::any value;
    AttrType type;
    
    // Constructors
    AttrValue(bool value)      : value(value), type(typeOf(value)) {}
    AttrValue(int value)       : value(value), type(typeOf(value)) {}
    AttrValue(long value)      : value(value), type(typeOf(value)) {}
    AttrValue(long long value) : value(value), type(typeOf(value)) {}
    AttrValue(float value)     : value(value), type(typeOf(value)) {}
    AttrValue(double value)    : value(value), type(typeOf(value)) {}
    
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

    // castings
    template <typename T>
    operator T() {
        std::cout << "assert(" << type_to_string(type) << " == " << type_to_string(typeOf(T())) << ")" << std::endl;
        assert(type == typeOf(T()));
        return std::experimental::any_cast<T>(value);
    }
    
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
    /*
    std::vector<AttrValue> vec = {"hola", 2};
    AttrValue val = vec;
    AttrValue val2 = val;
    std::string x = val2.asList().at(0);
    val2 = 2;
    int y = val2;
    std::cout << x << y << std::endl;
    */
    AttrValue val3 = 3LL;
    std::cout << AttrValue::type_to_string(val3.type) << std::endl;
    std::int64_t c = val3;
    std::cout << c << std::endl;
}