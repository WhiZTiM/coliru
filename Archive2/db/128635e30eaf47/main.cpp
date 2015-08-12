#include <vector>
#include<string>

typedef std::vector <std::string> strVector;

class Config
{
public:
    Config();
      void         addItem();
      strVector    myVector;
};

Config::Config(){}

 void Config::addItem(){
    myVector.push_back("Hi");
}

int main(int argc, char** argv)
{   
    Config c;
    c.addItem();
}