#include <iostream>

template <typename ValueType_>
class Foo{
    public:
    Foo(ValueType_ v){std::cout << "nonarr\n";}
    
    Foo(ValueType_ v[]){std::cout << "arr\n";}
    
};
    


int main(int , char **){
    
    Foo<int>(0);
}
