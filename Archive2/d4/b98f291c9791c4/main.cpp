#include <iostream>
#include <stack>
#include <string>

class Champ 
{
private: 
       int hp;
       std::string _class;
public:
       Champ();
       Champ(std::string chose);
};

Champ::Champ() {hp=10; _class="";}

Champ::Champ(std::string chose) {_class = chose;}


main()
{
     Champ Test;
     std::string chose;

     getline(std::cin,chose);

     Champ Test(chose);
    return 0;
}