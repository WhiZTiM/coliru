#include <iostream>
#include <vector>
#include <memory>

template <class T> class X{
    static typename T::S ts;
};

class Y {
private:
    class VS{ class S{ }; };
    X<VS> x;
};
int main(){
}