#include <string>
#include <iostream>

class MyClass{
    public:
    std::wstring msg = L"hey";
    MyClass(){};
};

class MyClass2{
    public:
    template<class T> MyClass2(T* t, int i=0);
};
template<class T>
MyClass2::MyClass2(T* t,int i){ std::wcout << t->msg << std::endl; }

int main(int argc, char **argv)
{
    MyClass mc;
    MyClass2 mc2(&mc);
    return 0;
}