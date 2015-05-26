#include<memory>

#include <iostream>
using namespace std;

using namespace std;

 struct Foo
{
    Foo() :
      s{new char[100]}
    {
        cout << "Constructor called!" << endl;  
    }

    Foo(const Foo& f) = delete;

    Foo(Foo&& f) :
      s{move(f.s)}
    {
        cout << "Move ctor called!" << endl;   
    }

    ~Foo() 
    { 
        cout << "Destructor called!" << endl;   
        cout << "s null? " << (s == nullptr) << endl;
    }

    unique_ptr<char[]> s;
};

void work(Foo&& f2)
{
    cout << "About to create f3..." << endl;
    Foo f3(move(f2));
    f3.~Foo();
}

int main()
{
    Foo f1;
    work(move(f1));
}