#include <iostream>
#include <unordered_set>

enum enm{
    One,
    Two
};

class Complex{
public:
void func(std::unordered_multiset<int> _v);
void name(std::unordered_multiset<int>::const_iterator i);
};

void Complex:: name(std::unordered_multiset<int>::const_iterator i){
    switch(*i){
            case One:
                std::cout<<"One"<<std::endl;
                break;
            case Two:
                std::cout<<"Two"<<std::endl;
                break;
        }
}

void Complex:: func(std::unordered_multiset<int> _v){
    _v.insert(One);
    _v.insert(Two);
    for (std::unordered_multiset<int>::const_iterator i(_v.begin()), end(_v.end()); i != end; ++i){
        name(i);
    }
}

int main(){
    Complex c;
    std::unordered_multiset<int> ms;
    c.func(ms);
    return 0;   
}