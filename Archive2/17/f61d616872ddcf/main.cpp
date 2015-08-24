#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
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
    return out << '(' << std::setw(2) << s.a <<
        		 ", " << std::setw(2) << s.b <<
				 ", " << std::setw(2) << s.c << ')';
}

Element generate_Element()
{
	static std::mt19937 gen{std::random_device{}()};
	static std::uniform_int_distribution<> dist(0, 10);
	//Return structure filled with 3 random values
	return {dist(gen), dist(gen), dist(gen)};
}

//A template helper I created to not clutter main()
template<typename T>
std::ostream& print(std::ostream& out, const T& cont)
{
    for(const auto& v: cont)
        out << v << '\n';
    return out;
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
    auto array = get_array();

	std::cout << "Array data:\n";
    print(std::cout, array) << '\n';
    
    array.erase(array.begin() + 2);
    
    std::cout << "Array data after erase:\n";
    print(std::cout, array) << '\n';
}
