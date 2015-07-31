#include <iostream>
#include <string>
#include <initializer_list>
#include <tuple>

class no_match : std::exception{
public:
    const char * what() const noexcept{
        return "No match found";
    }
};

template <typename AssociatedType_>
AssociatedType_ getMatch(
    const std::string &query,
    const std::initializer_list<std::pair<AssociatedType_, std::initializer_list<std::string>>> &cases
    ){
        
    // for every value associated with a list of aliases in the set
    for(auto &&commandAndAliases : cases){
        
        for(auto &&alias : commandAndAliases.second){
            if(query == alias){
                return commandAndAliases.first;
            }
        }
    }
    
    throw no_match{};
    
}

int main(){
    
    
    for(auto &&exampleQuery : {"v", "veggies", "vegetables", "fruit", "frutas", "nuts", "legumes", "rabbit"}){
        try{
        std::cout << getMatch<std::string>(exampleQuery, {
            {"Got Vegetables\n", {"v", "veggies", "vegetables"}},
            {"Got Fruit\n", {"f", "fruit", "frutas"}},
            {"Got Legumes\n", {"l", "nuts", "legumes"}}
            });
        }
        catch(no_match &e){
            std::cerr << e.what() << '\n';
        }
    }
}