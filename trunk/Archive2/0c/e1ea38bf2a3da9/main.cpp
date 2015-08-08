#include <sstream>
#include <iostream>
#include <typeindex>
#include <boost/variant.hpp>
#include <wiertlo/meta.hpp>
#include <wiertlo/enum_enable.hpp>

struct A { void print() const { std::cout << "A\n"; } };
struct B { void print() const { std::cout << "B\n"; } };
struct C { void print() const { std::cout << "C\n"; } };
struct D { void print() const { std::cout << "D\n"; } };
struct E { void print() const { std::cout << "E\n"; } };
struct F { void print() const { std::cout << "F\n"; } };
struct G { void print() const { std::cout << "G\n"; } };
struct H { void print() const { std::cout << "H\n"; } };
struct I { void print() const { std::cout << "I\n"; } };

typedef wiertlo::meta::TypeList<A, B, C, D, E, F, G, H, I> types;
typedef boost::variant<A, B, C, D, E, F, G, H, I> var;
var s;

template<typename T, typename U, typename std::enable_if<wiertlo::meta::Contains<types, T>::value && wiertlo::meta::Contains<types, U>::value>::type* = nullptr>
bool operator<(const T&, const U&)
{
    return typeid(T).before(typeid(U));
}

class my_visitor : public boost::static_visitor<void>
{
public:
	template<typename T>
	void operator()(const T& s) const
	{
		s.print();
	}
};

#define WIERTLO_ENUM_TYPE boost::variant<A, B, C, D, E, F, G, H, I>
#define WIERTLO_ENUM_NAME stuff
#define WIERTLO_ENUM_LIST \
	WIERTLO_ENUM_VALUE(a, var(A())) \
	WIERTLO_ENUM_VALUE(b, var(B())) \
	WIERTLO_ENUM_VALUE(c, var(C())) \
	WIERTLO_ENUM_VALUE(d, var(D())) \
	WIERTLO_ENUM_VALUE(e, var(E())) \
	WIERTLO_ENUM_VALUE(f, var(F())) \
	WIERTLO_ENUM_VALUE(g, var(G())) \
	WIERTLO_ENUM_VALUE(h, var(H())) \
	WIERTLO_ENUM_VALUE(i, var(I()))
#include <wiertlo/enum.hpp>

int main()
{
	std::cout << "This is the output, but I don't know how to put multiple headers on coliru\n";
	std::stringstream ss("ababacgihf");
	char z;
	while(ss.get(z))
	{
		std::string str(1, z);
		const var& asdf = stuff::from_string(str);
		boost::apply_visitor( my_visitor(), asdf );
	}
}

