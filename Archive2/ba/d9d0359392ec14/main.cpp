#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

struct S
{
    int a;
    int b;
    int c;
};

bool order_by_a(const S& lhs, const S& rhs)
{
    return lhs.a < rhs.a;
}

std::ostream& operator<<(std::ostream& out, const S& s)
{
    return out << '(' << std::setw(2) << s.a <<
    			 ", " << std::setw(2) << s.b <<
				 ", " << std::setw(2) << s.c << ')';
}

S generate_s()
{
	static std::mt19937 gen{std::random_device{}()};
	static std::uniform_int_distribution<> dist(0, 10);
	//Return structure filled with 3 random values
	return {dist(gen), dist(gen), dist(gen)};
}

//A template helper I created to not clutter main()
template<typename T>
std::ostream& print(std::ostream& out, T cont)
{
    for(const auto& v: cont)
        out << v << '\n';
    return out;
}

int main()
{
    std::cout << "How many array elements you want?\n";
    int size;
    std::cin >> size;

	//create vector of chosen size and fill it using generator function
    std::vector<S> array(size);
    std::generate(array.begin(), array.end(), generate_s);

	std::cout << "Unsorted:\n";
    print(std::cout, array) << '\n';

    //http://en.cppreference.com/w/cpp/algorithm/sort
    //Sort by a using comparison function
    std::sort(array.begin(), array.end(), order_by_a);

	std::cout << "Sorted by a:\n";
    print(std::cout, array) << '\n';

    //Sort by c using lambda function
    std::sort(array.begin(), array.end(),
              [](auto& lhs, auto& rhs) { return lhs.c < rhs.c; });

	std::cout << "Sorted by c:\n";
    print(std::cout, array) << '\n';
}
