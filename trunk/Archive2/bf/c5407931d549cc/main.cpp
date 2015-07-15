#include <vector>
#include <memory>
#include <iostream>


template<typename T>
struct FailStruct;

class Foo{
public:

    std::vector<int>& GetVector(){return m_bar;}
    std::vector<int> m_bar;
};

int main(int argc, char* argv[])
{
    Foo f;
    
    auto vec = f.GetVector();
    FailStruct<decltype(vec)> myStruct; //vector<int> gets deduced
    
    //auto& vec2 = f.GetVector();
    //FailStruct<decltype(vec2)> myStruct; //vector<int>& gets deduced
    std::cout << "Success" << std::endl;
    return 0;
}