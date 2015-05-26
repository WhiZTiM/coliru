#include<memory>

#include <iostream>

using namespace std;

struct Foo
{
    Foo()  
    {
        s = new char[100]; 
        cout << "Constructor called!" << endl;  
    }

    Foo(const Foo& f) = delete;

    Foo(Foo&& f) :
      s{f.s}
    {
        cout << "Move ctor called!" << endl;   
        f.s = nullptr;
    }

    Foo& operator=(Foo&& f)
    {
      cout << "Move assignment called!" << endl;   
      char* tmp{move(f.s)};
      delete[] s;
      f.s = nullptr;
      s = tmp;
      return *this;
    }

    ~Foo() 
    { 
        cout << "Destructor called!" << endl;   
        cout << "s null? " << (s == nullptr) << endl;
        delete[] s; // okay if s is NULL
    }

    char* s;
};

void workbad(Foo&& rfoo)
{
   cout << "About to create f3..." << endl;
    Foo f3(move(rfoo));
    rfoo.~Foo();
}

void work(Foo&& f2)
{
  static Foo f3{move(f2)};
}

void work2(Foo&& f4)
  {
    static Foo f5;
    cout << "About reassign f5..." << endl;
    f5 = move(f4);
  }

int main()
{
    Foo f1;
    work(move(f1));
    Foo f3;
    work2(move(f3));
    Foo last;
    workbad(move(last));
}
