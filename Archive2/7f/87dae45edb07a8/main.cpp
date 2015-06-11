#include <iostream>
#include <string>
#include <vector>
#include <memory>

struct A
    {    
	virtual ~A () {}
	};

std::unique_ptr<A> _Get ()
{
    struct enabler : public A {};
    return std::make_unique<enabler> ();
}
int main()
{
std::unique_ptr<A> ptr = _Get ();
}
