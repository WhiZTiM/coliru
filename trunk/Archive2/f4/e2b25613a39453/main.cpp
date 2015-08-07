#include <iostream>
#include <algorithm>
#include <string>

struct stuff
{
    std::string name;
    int year;
    int x;
    int y;
    int z;
};

//Comparator
bool compare_years(const stuff& lhs, const stuff& rhs)
{
    return lhs.year < rhs.year;
}

void print_stuff(const stuff& s)
{
    std::cout << s.name << ' ' << s.year << ' ' << s.x << ' ' << s.y << ' ' << s.z << '\n';
}

int main()
{
    const int size = 3;
    stuff array[size] = {{"Name", 2010, 12, 25, 1500}, {"NAme", 2011, 01, 15, 1111}, {"NAMe", 2010, 11, 01, 1200}};
    std::sort(array, array + size, compare_years);
    for(const auto& s: array) 
        print_stuff(s);
    std::cout << '\n';
    std::sort(array, array + size, [](auto& lhs, auto& rhs){ return lhs.z < rhs.z; });
    for(const auto& s: array) 
        print_stuff(s);
}