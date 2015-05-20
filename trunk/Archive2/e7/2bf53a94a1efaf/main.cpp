#include <iostream>
#include <set>

struct A{};

int main()
{
    std::set<A*> aset;
	aset.emplace();
	std::cout << aset.size() << std::endl;
    return 0;
}
