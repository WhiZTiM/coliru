#include <random>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <map>

class AttrValue;
using AttrList = std::vector<AttrValue>;
using AttrDict = std::map<std::string, AttrValue>;
    

class AttrValue
{
    using AttrList = std::vector<AttrValue>;
    using AttrDict = std::map<std::string, AttrValue>;
    using AttrDictInitList = std::initializer_list<AttrDict::value_type>;
    using AttrInitList = std::initializer_list<AttrValue>;
    
private:
    struct AttrValueBase {};

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
    
    /*
    template<typename T>
    AttrValue(T&& value) : ptr(new AttrValueDerived<T>(std::forward<T>(value))) {}
    */
    
    /*
    template<typename T, typename std::enable_if<std::is_convertible<T, std::vector<AttrValue>>::value>::type* = nullptr>
    AttrValue(T&& value) : ptr(new AttrValueDerived<std::vector<AttrValue>>(std::forward<T>(value)))
    {
        std::cout << "!vector" << std::endl;
    }
    */
    
    AttrValue(   int value) : ptr(new AttrValueDerived<   int>(value)) {}    
    AttrValue( float value) : ptr(new AttrValueDerived< float>(value)) {}
    AttrValue(double value) : ptr(new AttrValueDerived<double>(value)) {}
    
    AttrValue(AttrDictInitList&& value) : ptr(new AttrValueDerived<AttrDict>(std::forward<AttrDictInitList>(value))) {}
    AttrValue(AttrInitList&& value) : ptr(new AttrValueDerived<AttrList>(std::forward<AttrInitList>(value))) {}
    
    
    
    
    template<typename T>
    AttrValue(T&& value) : ptr(new AttrValueDerived<std::string>(std::forward<T>(value)))
    {
        static_assert(std::is_convertible<T, std::string>::value, "");
        std::cout << "!string" << std::endl;
    }
    
    /*
    template<typename T, typename std::enable_if<std::is_constructible<std::vector<AttrValue>, T>::value>::type* = nullptr>
    AttrValue(T&& value) : ptr(new AttrValueDerived<std::vector<AttrValue>>(std::forward<T>(value)))
    {
        static_assert(std::is_constructible<std::vector<AttrValue>, T>::value, "");
        std::cout << "!vector" << std::endl;
    }
    */
    template<typename T>
    void setValue(T&& value) 
    {
        ptr = new AttrValueDerived<T>(std::forward<T>(value));
    }
    
    template<class T>
    T& value()
    {
        return static_cast<AttrValueDerived<T>*>(ptr)->value;
    }
    
    AttrValue& at(size_t pos)
    {
        return value<AttrList>().at(pos);
    }
    
    AttrValue& at(const std::string& key)
    {
        return value<AttrDict>().at(key);
    }
};

int main() 
{
    //AttrValue list = {1.5f, 5, 23.1};
    AttrValue dict = {{"a", 3}, {"b", 4}};
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
    std::cout << dict.at(1).at(1).value<int>() << std::endl;
}