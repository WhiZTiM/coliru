#include <iostream>
#include <string>

using namespace std;

class base
{
public:
    virtual void func(string) = 0;
    void func()
    {
        func("salut"); // appelle func de derived
    }
  
};
  
class derived : public base
{
public:
    using base::func;
  
    void func(string)
    {
        cout << "derived";
    }
};
 
int main(){
  derived d;
  d.func(); // affiche "derived"
}