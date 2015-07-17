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
    typedef std::unordered_map<std::string, EnumValue> map_type ;
    typedef map_type::value_type map_value_type ;
        
    static const map_type& Enumerations()
    {
        static map_type enumerations {
            {ALPHA, EnumValue(ALPHA)}, 
            {BETA, EnumValue(BETA)},
            {GAMMA, EnumValue(GAMMA)}
            };
        
        return enumerations;
    }
    
    static const EnumValue& Alpha()
    {
        return Enumerations().find(ALPHA)->second;
    }
    
    static const EnumValue& Beta()
    {
         return Enumerations().find(BETA)->second;
    }
    
    static const EnumValue& Gamma()
    {
        return Enumerations().find(GAMMA)->second;
    }
    
    static const EnumValue& StringToEnumeration(std::string _in)
    {
        return Enumerations().find(_in)->second;
    }
    
    static const EnumValue& IDToEnumeration(int _id)
    {
        const auto& enumerations = Enumerations();
        auto iter = std::find_if(enumerations.cbegin(), enumerations.cend(), 
        [_id](const map_value_type& vt)
        { 
            return vt.second.id == _id;
        });
        return iter->second;
    }
    
    static const size_t size()
    {
        return Enumerations().size();
    }
};


int main()
{
    std::cout << MyEnum::Alpha().name << std::endl; // Alpha
    std::cout << MyEnum::Beta().name << std::endl; // Beta
    std::cout << MyEnum::Gamma().name << std::endl; // Gamma
    
    std::cout << MyEnum::StringToEnumeration(ALPHA).id << std::endl; //should give 0
    std::cout << MyEnum::IDToEnumeration(0).name << std::endl; //should give "Alpha"
    std::cout << static_cast<std::string>(MyEnum::Alpha()) << std::endl; // string conversion
    std::cout << static_cast<int>(MyEnum::Alpha()) << std::endl; // int conversion
}
