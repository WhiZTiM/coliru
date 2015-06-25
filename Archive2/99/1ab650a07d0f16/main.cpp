#include <iostream>
#include <utility>
#include <tuple>
 
struct interface 
{
    virtual void foo() = 0;
};
 
struct concrete : interface
{
    std::string _id;
	concrete(std::string id) : _id(id) {}
	void foo() override { std::cout << _id; }
};
 
struct decorator : interface {};
 
struct dec1 : decorator
{
	interface& _source;
	dec1(interface& source) : _source(source) {}
 	dec1(dec1& rhs) : dec1(static_cast<interface&>(rhs)) {}
 
	void foo() override
	{ 
		std::cout << "dec1(";
		_source.foo();
		std::cout << ")";         
	}
};
 
int main() {
	concrete t("t");
	dec1 d1(t);
	dec1 d2(d1);
	d2.foo();
 	return 0;
}