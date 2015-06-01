#include <vector>
#include <iostream>
#include <iomanip>
 
int main()
{
    std::vector<std::string> numbers;
 
    numbers.push_back("abc");
    std::string s = "def";
    numbers.push_back(std::move(s));
 
    std::cout << "vector holds: ";
    for (auto&& i : numbers) std::cout << std::quoted(i) << ' ';
    std::cout << "\nMoved-from string holds " << std::quoted(s) << '\n';
}