#include <thread>
#include <iostream>

using namespace std;

class Foo
{
public:
    void method(int a,float b)
    {
        cout<<"This method takes float and int\n";
    }
    void method(char a,char b)
    {
        cout<<"This method takes two characters\n";
    }
 };


int main()
{
    Foo foo;
    thread yay([&foo](char a, char b){ foo.method(a, b); }, 2, 3);
    yay.join();
}
