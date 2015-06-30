
#include <iostream>

char (*f)();

template<class T>
T func(){
    std::cout << "$$$" << std::endl;

}



int main(int argc, char *argv[])
{
    f =&func;
    f();
}