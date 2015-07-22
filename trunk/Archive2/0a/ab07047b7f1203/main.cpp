#include <iostream>
#include <vector>

class Format{
    public:
        std::vector<char> part_a_data = {};
        std::vector<float> part_b_data = {1.02f};
        std::vector<int> part_c_data = {69, 420};
        std::vector<char> part_d_data = {'y', 'o', 'l', 'o', '\0'};
};

class Parser{
    public:
        Parser(const std::string &filepath){}
        
        Format get_result(){return {};}
};


int main(){
    auto parser = Parser("test.my_format");
    auto result = parser.get_result();
    
    if(result.part_a_data.empty()){
        std::cout << "Part A empty\n";   
    }
    
    // do something with result part b, c and/or d
}
