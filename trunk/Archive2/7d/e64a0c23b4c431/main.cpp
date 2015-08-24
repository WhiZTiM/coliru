#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

struct Element
{
    int a;
    int b;
    int c;
};

bool order_by_a(const Element& lhs, const Element& rhs)
{
    return lhs.a < rhs.a;
}

std::ostream& operator<<(std::ostream& out, const Element& s)
{
    return out << '(' << s.a << ", " << s.b << ", " << s.c << ')';
}

Element generate_Element()
{
	return {rand(), rand(), rand()};
}

std::vector<Element> get_array()
{
    std::cout << "How many array elements you want?\n";
    int size;
    std::cin >> size;
    std::vector<Element> array(size);
    std::generate(array.begin(), array.end(), generate_Element);
    std::sort(array.begin(), array.end(), order_by_a);
    return array;
}

int main()
{
    srand(time(nullptr));
    auto array = get_array();

	std::cout << "Array data:\n";
    for(const auto& v: array)
        std::cout << v << '\n';
    std::cout << '\n';
    
    array.erase(array.begin() + 2);
    
    std::cout << "Array data after erase:\n";
    for(const auto& v: array)
        std::cout << v << '\n';
    std::cout << '\n';
}
