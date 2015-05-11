#include <initializer_list>
#include <iostream>

class Foo {
  public:
    friend void bar(std::initializer_list<Foo> v);
};

void bar(std::initializer_list<Foo> v) {
    std::cout << "size = " << v.size() << std::endl;
}
  
void baz(std::initializer_list<Foo> v) {
    std::cout << "size = " << v.size() << std::endl;
}

int main(){
    Foo a;
    bar({a,a});   // works now
    baz({a,a});   // works

    return 0;
}