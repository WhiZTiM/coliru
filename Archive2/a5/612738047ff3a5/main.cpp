#include <functional>
#include <iostream>
#include <memory>

class A {};
class B : public A{};

int main (){
B b;
if (std::is_base_of<A,decltype(b)>::value){
   std::cout<<"b can be up-cast to A*";
}
return 0;
}
