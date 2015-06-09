#include <iostream>

class Model {};

class Config : public Model {};

template <class T> 
class Access {};


class ConfigAccess : public Access<Config> {};

int main()
{
    ConfigAccess c;
    std::cout << "I compiled ok";    
}