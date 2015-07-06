#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

#define UNDEFINED "UNDEFINED"
#define PROPOSED "PROPOSED"
#define DRY "DRY"

struct PetrelWellPickClassification
{
    PetrelWellPickClassification(std::string _name): name(std::move(_name)), id(gid){++gid;}
    std::string name;
        int id;
    private:
        static int gid;
};

int PetrelWellPickClassification::gid = 0;

class PetrelWellPickClassifications
{
    public:
    static const PetrelWellPickClassification& Undefined;
    static const PetrelWellPickClassification& Proposed;
    static const PetrelWellPickClassification& Dry;
    static const PetrelWellPickClassification& StringToClassification(std::string _in)
    {
        return classifications.find(_in)->second;
    }
    
    static const PetrelWellPickClassification& NumberToClassification(int _in)
    {
        auto iter = std::find_if(classifications.cbegin(), classifications.cend(), 
        [&_in](const map_value_type& vt)
        { 
            return vt.second.id == _in;
        });
        return iter->second;
    }
    
    private:
    typedef std::unordered_map<std::string, PetrelWellPickClassification>  map_type ;
    typedef map_type::value_type map_value_type ;
    static const map_type classifications;
};


const std::unordered_map<std::string, PetrelWellPickClassification> PetrelWellPickClassifications::classifications =
{ 
    {UNDEFINED, PetrelWellPickClassification(UNDEFINED)}, 
    {PROPOSED,  PetrelWellPickClassification(PROPOSED)},
    {DRY,       PetrelWellPickClassification(DRY)}
};

const PetrelWellPickClassification& PetrelWellPickClassifications::Undefined  = classifications.find(UNDEFINED)->second;
const PetrelWellPickClassification& PetrelWellPickClassifications::Proposed  = classifications.find(PROPOSED)->second;
const PetrelWellPickClassification& PetrelWellPickClassifications::Dry  = classifications.find(DRY)->second;


int main()
{
    std::cout << "Hello world" << std::endl;
    std::cout << PetrelWellPickClassifications::Undefined.name << std::endl;
    std::cout << PetrelWellPickClassifications::Proposed.name << std::endl;
    std::cout << PetrelWellPickClassifications::Dry.name << std::endl;
    
    
    std::cout << PetrelWellPickClassifications::StringToClassification(UNDEFINED).id << std::endl; //should give 0
    std::cout << PetrelWellPickClassifications::NumberToClassification(0).name << std::endl; //should give 1
}
