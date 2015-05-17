#include <typeinfo>

struct base {
    int i = 0;
    virtual void foo() {}
};

struct derived: virtual base {};

int main()
{
    derived d;
    base& b = d;
    
    if(auto p = dynamic_cast<derived*>(&b)) {
        return p->i;
    }
    
    if(typeid(b) == typeid(derived)) {
        return static_cast<derived&>(b).i;
    }
}
