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
    
private:
    struct AttrValueBase {
        virtual ~AttrValueBase() = default;
    };

    template<typename T>
    struct AttrValueDerived : AttrValueBase
    {
        T value;
        
        template<typename U>
        AttrValueDerived(U&& value) : value(std::forward<U>(value)) {}
    };
    
    AttrValueBase* ptr;
    
public:
    AttrValue() : ptr(nullptr) {}
    
    AttrValue(   int value) : ptr(new AttrValueDerived<   int>(value)) { std::cout << "AttrValue(   int value)" << std::endl; }    
    AttrValue( float value) : ptr(new AttrValueDerived< float>(value)) { std::cout << "AttrValue( float value)" << std::endl; }
    AttrValue(double value) : ptr(new AttrValueDerived<double>(value)) { std::cout << "AttrValue(double value)" << std::endl; }
    
    AttrValue(const char* value) : ptr(new AttrValueDerived<std::string>(value)) { std::cout << "AttrValue(const char* value)" << std::endl; }
    AttrValue(const std::string& value) : ptr(new AttrValueDerived<std::string>(value)) { std::cout << "AttrValue(const std::string& value)" << std::endl; }
    
    AttrValue(const     List&  value) : ptr(new AttrValueDerived<List>(          value )) { std::cout << "AttrValue(const     List&  value)" << std::endl; }
    AttrValue(          List&& value) : ptr(new AttrValueDerived<List>(std::move(value))) { std::cout << "AttrValue(          List&& value)" << std::endl; }
    AttrValue(const InitList&  value) : ptr(new AttrValueDerived<List>(          value )) { std::cout << "AttrValue(const InitList&  value)" << std::endl; }
    AttrValue(      InitList&& value) : ptr(new AttrValueDerived<List>(std::move(value))) { std::cout << "AttrValue(      InitList&& value)" << std::endl; }
    
    AttrValue(const Dict&          value) : ptr(new AttrValueDerived<Dict>(          value )) { std::cout << "AttrValue(const Dict&          value)" << std::endl; }
    AttrValue(      Dict&&         value) : ptr(new AttrValueDerived<Dict>(std::move(value))) { std::cout << "AttrValue(      Dict&&         value)" << std::endl; }
    AttrValue(const DictInitList&  value) : ptr(new AttrValueDerived<Dict>(          value )) { std::cout << "AttrValue(const DictInitList&  value)" << std::endl; }
    AttrValue(      DictInitList&& value) : ptr(new AttrValueDerived<Dict>(std::move(value))) { std::cout << "AttrValue(      DictInitList&& value)" << std::endl; }
    
    template<typename T>
    void setValue(T&& value) 
    {
        ptr = new AttrValueDerived<T>(std::forward<T>(value));
    }
    
    template<class T>
    T& value()
    {
        auto ptrAux = dynamic_cast<AttrValueDerived<T>*>(ptr);
        assert(ptrAux != nullptr);
        return ptrAux->value;
        
        return static_cast<AttrValueDerived<T>*>(ptr)->value;
    }
    
    AttrValue& at(size_t pos)
    {
        return value<List>().at(pos);
    }
    
    AttrValue& at(const std::string& key)
    {
        return value<Dict>().at(key);
    }
};

using AttrList = AttrValue::List;
using AttrDict = AttrValue::Dict;


int main() 
{
    
    AttrValue list = {1.5f, 5, 23.1, {"!", 123.2}};
    AttrValue dict = AttrDict{{"a", 3}, {"b", 4}};
    list = {1};
    AttrValue dict2 = dict;
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
    //std::cout << list.at(1).value<int>() << std::endl;
    std::cout << dict.at("b").value<int>() << std::endl;
    std::cout << dict2.at("a").value<int>() << std::endl;
}