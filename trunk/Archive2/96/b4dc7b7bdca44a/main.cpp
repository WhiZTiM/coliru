#include <iostream>
#include <vector>
#include <algorithm>

struct data
{
    int id;
	int value;
};

struct 
{
	bool operator()(const data & lhs, const data & rhs) { return lhs.id < rhs.id; }
} CompareId;

struct 
{
	bool operator()(const data & lhs, const data & rhs) { return lhs.value < rhs.value; }
} CompareValue;

int main()
{
	std::vector<data> database{ { 1,5 },{ 2,10 },{ 3,5 },{ 4,8 },{ 5,3 } };
	std::sort(database.begin(), database.end(), CompareValue);
	for (const auto & e : database)
		std::cout << e.id << "\t" << e.value << std::endl;
	std::sort(database.begin(), database.end(), CompareId);
	std::cout << std::endl;
	for (const auto & e : database)
		std::cout << e.id << "\t" << e.value << std::endl;
	return 0;
}
