#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

#define ALPHA "Alpha"

#define BETA "Beta"

#define GAMMA "Gamma"

struct EnumValue
{
    EnumValue(std::string _name): name(std::move(_name)), id(gid){++gid;}
    std::string name;
    int id;
    operator std::string() const
    {
        return name;
    }
    
    operator int() const
    {
        return id;
    }
    
    private:
        static int gid;
};

int EnumValue::gid = 0;

class MyEnum
{
    public:
    static const EnumValue& Alpha;
    static const EnumValue& Beta;
    static const EnumValue& Gamma;
    static const EnumValue& StringToEnumeration(std::string _in)
    {
        return enumerations.find(_in)->second;
    }
    
    static const EnumValue& IDToEnumeration(int _id)
    {
        auto iter = std::find_if(enumerations.cbegin(), enumerations.cend(), 
        [_id](const map_value_type& vt)
        { 
            return vt.second.id == _id;
        });
        return iter->second;
    }
    
    static const size_t size()
    {
        return enumerations.size();
    }
    
    private:
    typedef std::unordered_map<std::string, EnumValue>  map_type ;
    typedef map_type::value_type map_value_type ;
    static const map_type enumerations;
};


const std::unordered_map<std::string, EnumValue> MyEnum::enumerations =
{ 
    {ALPHA, EnumValue(ALPHA)}, 
    {BETA, EnumValue(BETA)},
    {GAMMA, EnumValue(GAMMA)}
};

const EnumValue& MyEnum::Alpha = enumerations.find(ALPHA)->second;
const EnumValue& MyEnum::Beta  = enumerations.find(BETA)->second;
const EnumValue& MyEnum::Gamma  = enumerations.find(GAMMA)->second;


int main()
{
    std::cout << MyEnum::Alpha.name << std::endl; // Alpha
    std::cout << MyEnum::Beta.name << std::endl; // Beta
    std::cout << MyEnum::Gamma.name << std::endl; // Gamma
    
    std::cout << MyEnum::StringToEnumeration(ALPHA).id << std::endl; //should give 0
    std::cout << MyEnum::IDToEnumeration(0).name << std::endl; //should give "Alpha"
    std::cout << static_cast<std::string>(MyEnum::Alpha) << std::endl; // string conversion
    std::cout << static_cast<int>(MyEnum::Alpha) << std::endl; // int conversion
}
