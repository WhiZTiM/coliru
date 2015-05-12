#include <thread>
#include <iostream>

struct A {

void func (){
    std::cout<<"hello\n";
}
    
};

int main (void){

A a;
std::thread t ([&]{
    a.func();
});

t.join();

return 0;    
}