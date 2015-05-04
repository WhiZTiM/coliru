#include <iostream>
#include <vector>
#include <iterator>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};
	std::vector<int> vec_second = {6, 7};

	auto it = vec.begin() + 2;
	//it = 

	if((it = vec.erase(it, it + vec_second.size())) == vec.end())
	{
		vec.reserve(vec.size() + vec_second.size());
		vec.insert(vec.end(), vec_second.begin(), vec_second.end());
	}
	else
		vec.insert(it, vec_second.begin(), vec_second.end());

	for(auto const& x : vec)
		cout << x << " ";

	cin.get();
}