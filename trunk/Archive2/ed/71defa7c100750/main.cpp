#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <functional>
#include <boost/variant.hpp>

struct A { void print() const { std::cout << "A\n"; } };
struct B { void print() const { std::cout << "B\n"; } };
struct C { void print() const { std::cout << "C\n"; } };
struct D { void print() const { std::cout << "D\n"; } };
struct E { void print() const { std::cout << "E\n"; } };
struct F { void print() const { std::cout << "F\n"; } };
struct G { void print() const { std::cout << "G\n"; } };
struct H { void print() const { std::cout << "H\n"; } };
struct I { void print() const { std::cout << "I\n"; } };

typedef boost::variant<A, B, C, D, E, F, G, H, I> var;

std::unordered_map<std::string, std::function<var()>> factory = {
    { "a", []() -> var { return A(); }},
    { "b", []() -> var { return B(); }},
    { "c", []() -> var { return C(); }},
    { "d", []() -> var { return D(); }},
    { "e", []() -> var { return E(); }},
    { "f", []() -> var { return F(); }},
    { "g", []() -> var { return G(); }},
    { "h", []() -> var { return H(); }},
    { "i", []() -> var { return I(); }},
};

class my_visitor : public boost::static_visitor<void>
{
public:
    template<typename T>
	void operator()(const T& s) const
	{
		s.print();
	}
};

int main()
{
	std::stringstream ss("ababacgihf");
	char z;
	while(ss.get(z))
	{
		std::string str(1, z);
		const var& asdf = factory.at(str)();
		boost::apply_visitor( my_visitor(), asdf );
	}
}

