#include <iostream>
#include <string>

using std::cout;
using std::endl;

struct myStruct_t
{
    myStruct_t ()
    {
        cout << "**Ctor!"<< endl;
    }
    ~myStruct_t ()
    {
        cout << "**Dtor!"<< endl;
    }
    void foo () const
    {
        cout << "Foo!" << endl;
    }
};
    
myStruct_t fn ()
{
    return myStruct_t ();
}

int main()
{
    cout << "Hello" << endl;
    {
        // Const reference to a temporary:
        const myStruct_t& r = fn ();
        r.foo ();
    }
    cout << "Goodbye" << endl;
    return 0;
}