
#include <iostream>

char (*f)(char);

template<class T>
T func(T v){
    std::cout << "$$$" << std::endl;

}



int main(int argc, char *argv[])
{
    f =&func;
    f('a');
}