#include <iostream>
#include <set>

struct A{};

bool operator<(const A&, const A&) { return true;}

int main()
{
    std::set<A> aset;
	aset.emplace();
	std::cout << aset.size() << std::endl;
    return 0;
}
