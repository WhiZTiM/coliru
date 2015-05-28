#include <random>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <map>
#include <algorithm>

class AttrValue
{
public:
    using List = std::vector<AttrValue>;
    using Dict = std::map<std::string, AttrValue>;
    
private:
    using InitList = std::initializer_list<AttrValue>;
    using DictInitList = std::initializer_list<Dict::value_type>;
    
public:
    enum class AttrType : uint8_t {INTEGER, FLOAT, DOUBLE, STRING, LIST, DICTIONARY, UNKNOWN};

private:
    static std::string attrType_to_string(AttrType type)
    {
        switch(type) {
            case AttrType::INTEGER: return "INTEGER";
            case AttrType::FLOAT: return "FLOAT";
            case AttrType::DOUBLE: return "DOUBLE";
            case AttrType::STRING: return "STRING";
            case AttrType::LIST: return "LIST";
            case AttrType::DICTIONARY: return "DICTIONARY";
            case AttrType::UNKNOWN: return "UNKNOWN";
        }
        assert(false);
        return "ERROR";
    }

    static constexpr AttrType attrType_of(int) { return AttrType::INTEGER; }
    static constexpr AttrType attrType_of(float) { return AttrType::FLOAT; }
    static constexpr AttrType attrType_of(double) { return AttrType::DOUBLE; }
    static constexpr AttrType attrType_of(const std::string&) { return AttrType::STRING; }
    static constexpr AttrType attrType_of(const List&) { return AttrType::LIST; }
    static constexpr AttrType attrType_of(const Dict&) { return AttrType::DICTIONARY; }
    static constexpr AttrType attrType_of(...) { return AttrType::UNKNOWN; }
    
private:
    struct AttrValueBase {
        AttrType type;
        AttrValueBase(AttrType type) : type(type) { std::cout << attrType_to_string(type) << std::endl; }
        virtual ~AttrValueBase() = default;
    };

    template<typename T>
    struct AttrValueDerived : AttrValueBase
    {
        T value;
        
        template<typename U>
        AttrValueDerived(U&& value) : AttrValueBase(attrType_of(value)), value(std::forward<U>(value)) {}
    };
    
    AttrValueBase* ptr;
    
public:
    AttrValue() : ptr(nullptr) {}
    
    //AttrValue(const AttrValue&  value) : ptr(nullptr) { std::cout << "AttrValue(const AttrValue&  value)" << std::endl; }
    //AttrValue(      AttrValue&& value) : ptr(value.ptr)               { std::cout << "AttrValue(      AttrValue&& value)" << std::endl; }
    
    AttrValue(   int value) : ptr(new AttrValueDerived<   int>(value)) { std::cout << "AttrValue(   int value)" << std::endl; }    
    AttrValue( float value) : ptr(new AttrValueDerived< float>(value)) { std::cout << "AttrValue( float value)" << std::endl; }
    AttrValue(double value) : ptr(new AttrValueDerived<double>(value)) { std::cout << "AttrValue(double value)" << std::endl; }
    
    AttrValue(const char* value)        : ptr(new AttrValueDerived<std::string>(value)) { std::cout << "AttrValue(const char* value)" << std::endl; }
    AttrValue(const std::string& value) : ptr(new AttrValueDerived<std::string>(value)) { std::cout << "AttrValue(const std::string& value)" << std::endl; }
    
    AttrValue(const     List&  value) : ptr(new AttrValueDerived<List>(          value )) { std::cout << "AttrValue(const     List&  value)" << std::endl; }
    AttrValue(          List&& value) : ptr(new AttrValueDerived<List>(std::move(value))) { std::cout << "AttrValue(          List&& value)" << std::endl; }
    AttrValue(const InitList&  value) : ptr(new AttrValueDerived<List>(          value )) { std::cout << "AttrValue(const InitList&  value)" << std::endl; }
    AttrValue(      InitList&& value) : ptr(new AttrValueDerived<List>(std::move(value))) { std::cout << "AttrValue(      InitList&& value)" << std::endl; }
    
    AttrValue(const Dict&          value) : ptr(new AttrValueDerived<Dict>(          value )) { std::cout << "AttrValue(const Dict&          value)" << std::endl; }
    AttrValue(      Dict&&         value) : ptr(new AttrValueDerived<Dict>(std::move(value))) { std::cout << "AttrValue(      Dict&&         value)" << std::endl; }
    AttrValue(const DictInitList&  value) : ptr(new AttrValueDerived<Dict>(          value )) { std::cout << "AttrValue(const DictInitList&  value)" << std::endl; }
    AttrValue(      DictInitList&& value) : ptr(new AttrValueDerived<Dict>(std::move(value))) { std::cout << "AttrValue(      DictInitList&& value)" << std::endl; }
    
    AttrType type() const
    {
        return ptr->type;
    }
    
    template <typename T>
    T& value()
    {
        assert(type() == attrType_of(T()));
        return static_cast<AttrValueDerived<T>*>(ptr)->value;
    }
    
    /*
    AttrValue& operator=(const AttrValue& value) {
        std::cout << "operator=(const AttrValue& value)" << std::endl;
        AttrValue tmp(value);
        std::swap(*this, tmp);
        return *this;
    }
    */
    
    AttrValue& operator=(AttrValue&& value) {
        std::cout << "operator=(AttrValue&& value)" << std::endl;
        std::swap(*this, value);
        return *this;
    }
    
    AttrValue& operator[](size_t pos) { return value<List>()[pos]; }
    AttrValue& at(size_t pos) { return value<List>().at(pos); }
    
    AttrValue& operator[](const std::string& key) { return value<Dict>()[key]; }
    AttrValue& at(const std::string& key) { return value<Dict>().at(key); }
    
    size_t size()
    {
        if (type() == AttrType::LIST)
        {
            return value<List>().size();
        }
        else if (type() == AttrType::DICTIONARY)
        {
            return value<Dict>().size();
        }
        else
        {
            assert(false);
            return 0;
        }
    }
    
    bool empty()
    {        
        if (type() == AttrType::LIST)
        {
            return value<List>().empty();
        }
        else if (type() == AttrType::DICTIONARY)
        {
            return value<Dict>().empty();
        }
        else
        {
            assert(false);
            return true;
        }
    }
};

using AttrList = AttrValue::List;
using AttrDict = AttrValue::Dict;


int main() 
{
    AttrValue list = {1,2,3};
    std::cout << "SIZE: " << list.size() << std::endl;
    list = {1};
    
    //AttrValue list2 = AttrList{};
    //std::cout << "SIZE: " << list2.size() << std::endl;
    
    //AttrValue dict = AttrDict{{"a", 3}, {"b", 4}};
    //std::cout << "SIZE: " << dict.size() << std::endl;
    
    std::cout << "value: " << list.value<AttrList>().at(1).value<int>() << std::endl;
    
    /*
    AttrValue attr;
    attr.setValue(21.5f);
    std::cout << attr.value<float>() << std::endl;
    attr.setValue(12);
    std::cout << attr.value<int>() << std::endl;
    attr.setValue(AttrList{1, 'a'});
    
    std::cout << dict.at("num").value<int>() << std::endl;
    std::cout << list.at(2).value<double>() << std::endl;
    std::cout << dict.at("list").value<AttrList>().at(1).value<char>() << std::endl;*/
    //std::cout << list.at(1).value() << std::endl;
    //std::cout << dict.at("b").value<int>() << std::endl;
    //std::cout << dict2.at("a").value<int>() << std::endl;
}