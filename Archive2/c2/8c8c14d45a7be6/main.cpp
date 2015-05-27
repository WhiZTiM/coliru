#include <random>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <map>

class AttrValue
{
public:
    using List = std::vector<AttrValue>;
    using InitList = std::initializer_list<AttrValue>;
    using Dict = std::map<std::string, AttrValue>;
    using DictInitList = std::initializer_list<Dict::value_type>;
    
    enum class AttrType : uint8_t {INTEGER, FLOAT, DOUBLE, STRING, LIST, DICTIONARY, UNKNOWN};
    
    static AttrType constexpr attrType_of(int) { return AttrType::INTEGER; }
    static AttrType constexpr attrType_of(float) { return AttrType::FLOAT; }
    static AttrType constexpr attrType_of(double) { return AttrType::DOUBLE; }
    static AttrType constexpr attrType_of(const std::string&) { return AttrType::STRING; }
    static AttrType constexpr attrType_of(const List&) { return AttrType::LIST; }
    static AttrType constexpr attrType_of(const Dict&) { return AttrType::DICTIONARY; }
    static AttrType constexpr attrType_of(...) { return AttrType::UNKNOWN; }
        
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
    
    template <AttrType ...>
    struct type_of { using type = void; };
    
private:
    struct AttrValueBase {
        const AttrType type;
        AttrValueBase(AttrType type) : type(type) { std::cout << attrType_to_string(type) << std::endl; }
        virtual ~AttrValueBase() = default;
    };

    template<typename T>
    struct AttrValueDerived : AttrValueBase
    {
        const T value;
        
        template<typename U>
        AttrValueDerived(U&& value) : AttrValueBase(attrType_of(value)), value(std::forward<U>(value)) {}
    };
    
    const AttrValueBase* ptr;
    
public:
    AttrValue() : ptr(nullptr) {}
    
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
    
    template<typename T>
    void setValue(T&& value) 
    {
        ptr = new AttrValueDerived<T>(std::forward<T>(value));
    }
    
    //template<class T>
    auto value() -> decltype(ptr->type == AttrType::INTEGER)
    {
        assert( type() == attrType_of(T()) );
        /*
        auto ptrAux = dynamic_cast<AttrValueDerived<T>*>(ptr);
        assert(ptrAux != nullptr);
        return ptrAux->value;
        */
        //return static_cast<AttrValueDerived<type_of<type()>::type>*>(ptr)->value;
        return true;
    }
    
    /*
    AttrValue& operator[](size_t pos)
    {
        return value<List>()[pos];
    }
    
    AttrValue& at(size_t pos)
    {
        return value<List>().at(pos);
    }
    
    size_t size()
    {
        return value<List>().size();
    }
    
    bool empty()
    {
        return value<List>().empty();
    }
    
    
    AttrValue& operator[](const std::string& key)
    {
        return value<Dict>()[key];
    }
    
    AttrValue& at(const std::string& key)
    {
        return value<Dict>().at(key);
    }
    
    Dict::size_type size()
    {
        return value<Dict>().size();
    }
    
    bool empty()
    {
        return value<Dict>().empty();
    }
    */
};

template <> struct AttrValue::type_of<AttrValue::AttrType::INTEGER   > { using type = int; };
template <> struct AttrValue::type_of<AttrValue::AttrType::FLOAT     > { using type = float; };
template <> struct AttrValue::type_of<AttrValue::AttrType::DOUBLE    > { using type = double; };
template <> struct AttrValue::type_of<AttrValue::AttrType::STRING    > { using type = std::string; };
template <> struct AttrValue::type_of<AttrValue::AttrType::LIST      > { using type = AttrValue::List; };
template <> struct AttrValue::type_of<AttrValue::AttrType::DICTIONARY> { using type = AttrValue::Dict; };

using AttrList = AttrValue::List;
using AttrDict = AttrValue::Dict;


int main() 
{
    
    AttrValue list = {1.5f, 5, 23.1, {"!", 123.2}};
    //std::cout << "SIZE: " << list.size() << std::endl;
    
    AttrValue list2 = AttrList{};
    //std::cout << "SIZE: " << list2.size() << std::endl;
    
    AttrValue dict = AttrDict{{"a", 3}, {"b", 4}};
    //std::cout << "SIZE: " << dict.size() << std::endl;
    
    std::cout << "value: " << list.value() << std::endl;
    
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