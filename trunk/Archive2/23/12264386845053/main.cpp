#include <vector>
#include <memory>
#include <iostream>


template<typename T>
struct FailStruct;

class Foo{
public:

    const std::vector<int>& GetVector(){return m_bar;}
    std::vector<int> m_bar;
};

int main(int argc, char* argv[])
{
    Foo f;
    f.m_bar.emplace_back(1);
    
   // auto vec = f.GetVector();
    //FailStruct<decltype(vec)> myStruct; //vector<int> gets deduced
    
    auto& vec2 = f.GetVector();
    //FailStruct<decltype(vec2)> myStruct; //vector<int>& gets deduced
    std::cout << "Success" << vec2[0] << std::endl;
    return 0;
}