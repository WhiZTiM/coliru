#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int main()
{
    std::vector<double> vec{ 1, 2, 3.456, 99.99 };
	std::unordered_map<std::string, std::string> beers{
		{"Thier","Dortmund"},
        {"Krombacher","Kreuztal"},
        {"Fiege","Bochum"}
	};
    for (const auto& beer : beers)
        std::cout << beer.first << ", " << beer.second << std::endl;
}