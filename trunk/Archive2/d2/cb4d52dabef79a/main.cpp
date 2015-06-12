#include <iostream>
#include <sstream>
#include <string>

class abc{
public:
    abc(int x) : x_{x}{}
    void print(){
        std::cout << x_ << std::endl;
    }
protected:
    int x_; 
    void setOther(abc &a){a.x_ = 1;}
};
class b: public abc{
public:
    b() : abc{1} {}
public :
    void something(abc &a){ 
        setOther(a);
    }
};
int main()
{
    abc
        alphabet{2};
    b
        beta{};
    
    alphabet.print();
    beta.something(alphabet);
    alphabet.print();
}
