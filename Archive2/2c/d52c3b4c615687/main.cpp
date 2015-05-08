#include <iostream>
#include <string>

using std::cout;
using std::endl;

struct Base
{
    ~Base ()
    {
        cout << "**Base dtor!" << endl;
    }
};

struct myStruct_t : public Base
{
    myStruct_t ()
    {
        cout << "**Derived ctor!"<< endl;
    }
    
    ~myStruct_t ()
    {
        cout << "**Derived dtor!"<< endl;
    }
};
    
myStruct_t fn ()
{
    return myStruct_t ();
}

int main()
{
    cout << "Calling fn ()..." << endl;
    const Base& r = fn ();
    cout << "Called fn ()..." << endl;        
    return 0;
}