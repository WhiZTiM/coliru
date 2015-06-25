#include <iostream>
#include <utility>
#include <type_traits>
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
    
    template<typename T, typename = typename std::enable_if<std::is_base_of<interface, T>::value>::type>
 	dec1(T& source) : _source(static_cast<interface&>(source)) {}
 
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