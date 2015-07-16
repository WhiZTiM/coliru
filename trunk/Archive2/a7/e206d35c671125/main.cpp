#include <vector>
#include <memory>
#include <iostream>
#include <boost/filesystem.hpp>


template<typename T>
struct FailStruct;

class Foo{
public:

    const std::vector<int>& GetVector(){return m_bar;}
    std::vector<int> m_bar;
};

int main(int argc, char* argv[])
{
    boost::filesystem::path path("foo");
    
    auto&& fname = path.filename().string();
    
    std::cout << "Hello world " << fname << std::endl;
    return 0;
}