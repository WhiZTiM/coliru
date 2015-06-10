#include <iostream>
class A
{
public:
   class B{ public: ~B(){ std::cout << "B dtor" << '\n'; } };
   A() { p = new B(); }
   operator B*() { return p; }
private:
   B* p;
};

int main()
{
   A* a = new A();
   delete *a;
   std::cout << "end" << '\n';
}