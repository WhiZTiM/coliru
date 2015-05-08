#include <iostream>
#include <string>
#include <unordered_map>

class Toto
{
private:
    std::string _a;
public:
    Toto(std::string a) : _a(a) { };
    std::string getA() const { return _a; };
};

typedef std::unordered_map<std::string, Toto> MesTotos;

int main()
{
    Toto v("Hello");
    
    MesTotos map;
    
    map["prout"] = Toto("Yep");
    
    std::cout << v.getA() << std::endl;
}
