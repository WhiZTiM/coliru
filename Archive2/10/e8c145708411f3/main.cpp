#include <iostream>
#include <string>
#include <vector>

std::vector<int> vec;
void find(std::vector<int>::iterator& iter, std::vector<int>::iterator end, int test)
{
    while (iter != end) { 
		if (*iter == test)
			return;
		++iter;
	}
}

int main()
{
	std::vector<int> a = { 2,3,4 };
	std::vector<int>::iterator it = a.begin();
	find(it, a.end(), 5);
    if(it == a.end())
        std::cout << "Not found";
    else
        std::cout << "Found";
}

