#include <sstream>
#include <iostream>
#include <typeindex>
#include <wiertlo/enum_enable.hpp>

struct Base { virtual void print() const { std::cout << "Base\n"; } };
struct A : Base { virtual void print() const { std::cout << "A\n"; } };
struct B : Base { virtual void print() const { std::cout << "B\n"; } };
struct C : Base { virtual void print() const { std::cout << "C\n"; } };
struct D : Base { virtual void print() const { std::cout << "D\n"; } };
struct E : Base { virtual void print() const { std::cout << "E\n"; } };
struct F : Base { virtual void print() const { std::cout << "F\n"; } };
struct G : Base { virtual void print() const { std::cout << "G\n"; } };
struct H : Base { virtual void print() const { std::cout << "H\n"; } };
struct I : Base { virtual void print() const { std::cout << "I\n"; } };

bool operator<(const Base& lhs, const Base& rhs)
{
    return std::type_index(typeid(lhs)) < std::type_index(typeid(rhs));
}

#define WIERTLO_ENUM_TYPE Base
#define WIERTLO_ENUM_NAME stuff
#define WIERTLO_ENUM_LIST \
	WIERTLO_ENUM_VALUE(a, A()) \
	WIERTLO_ENUM_VALUE(b, B()) \
	WIERTLO_ENUM_VALUE(c, C()) \
	WIERTLO_ENUM_VALUE(d, D()) \
	WIERTLO_ENUM_VALUE(e, E()) \
	WIERTLO_ENUM_VALUE(f, F()) \
	WIERTLO_ENUM_VALUE(g, G()) \
	WIERTLO_ENUM_VALUE(h, H()) \
	WIERTLO_ENUM_VALUE(i, I())
#include <wiertlo/enum.hpp>

int main()
{
	std::stringstream ss("ababacgihf");
	char z;
	while(ss.get(z))
	{
		std::string str(1, z);
		const Base& asdf = stuff::from_string(str);
		asdf.print();
	}
}