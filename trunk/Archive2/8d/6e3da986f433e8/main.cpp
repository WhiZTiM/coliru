#include <iostream>
#include <string>
#include <tuple>

std::string serialize(const std::string& s)
{
    return "\"" + s + "\"";
}

std::string serialize(int x)
{
	return std::to_string(x);
}

template<class... Ts>
std::string serialize(const std::tuple<Ts...>& tup)
{
	std::string s = "{ ";
	bool first = true;
	for (const auto& member : { serialize(std::get<Ts>(tup))... })
	{
    	if (!first) {
			s += ", ";
		}
		s += member;
		first = false;
	}
	s += "}";
	return s;
}

struct Name { std::string value; };

std::string serialize(const Name& name)
{
	return std::string("Name : ") + serialize(name.value);
}

struct Age { int value; };

std::string serialize(const Age& age)
{
	return std::string("Age : ") + serialize(age.value);
}

int main()
{
	using Person = std::tuple<Name,Age>;
	
	Person p;
	std::get<Name>(p) = { "Joe" };
	std::get<Age>(p) = { 30 };
	
	std::cout << serialize(p) << std::endl;
}