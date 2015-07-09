#include <iostream>
#include <string>
#include <cassert>

// hidden in cpp file
std::string base;

// exposed
std::string Base()
{
    assert(!base.empty());
    return base;
}

// exposed but will only work first time
void SetBase(const std::string& dir)
{
    if (base.empty())
        base = dir;
}

int main(int argc, char** argv)
{
    SetBase("c:/crisps/walkers/");
    std::cerr << Base() << "salt" << std::endl;
    std::cerr << Base() << "prawns" << std::endl;
    
    SetBase("c:/ocean/contents/");
    std::cerr << Base() << "salt" << std::endl;
    std::cerr << Base() << "prawns" << std::endl;
}
