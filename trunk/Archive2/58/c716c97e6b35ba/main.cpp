#include <iostream>
#include <unordered_map>

struct NoCopyCtor
{
	NoCopyCtor(const NoCopyCtor&) = delete;
};


int main ()
{
    std::unordered_map<void*, NoCopyCtor> map;
    
    return 0;
}
