#include <iostream>

class Struct {
public:
   Struct() { std::cout << "0" << std::endl; }
   Struct(Struct&) { std::cout <<"1"<<std::endl;}
   Struct(const Struct&) { std::cout << "2" << std::endl; }
};

class Struct2 {
public:
    Struct s;
    
    Struct2() {}
    void setMember(const Struct& aux) { s = aux; }
};

int main()
{
    Struct s;
    Struct2 s2;
    s2.setMember(s);
}