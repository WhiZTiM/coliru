#include <map>
#include <functional>
#include <typeinfo>
#include <typeindex>
#include <iostream>

// 完美转发+分段构造
class MyClass
{
public:
    int a;
	int b;

	MyClass(int a, int b) : a(a), b(b) {}
};

std::map<std::type_index, MyClass> myMap;

template<class T, typename... Args>
T &Test(Args&&... args)
{
	auto it = myMap.emplace(std::forward<Args>(args)...);
	return it.first->second;
}

int main()
{
	// g++ 4.8+
	auto ref = Test<MyClass>(
		std::piecewise_construct, 
		std::forward_as_tuple<std::type_index>(typeid(MyClass)), 
		std::forward_as_tuple<int, int>(10, 100)
	);

	std::cout<<ref.a<<", "<<ref.b<<std::endl;

	return 0;
}