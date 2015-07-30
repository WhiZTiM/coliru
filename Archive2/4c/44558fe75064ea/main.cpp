#include <algorithm>
#include <iostream>

int main()
{
    int a[] {7, 11, 13};
	int counter=0;
	for (int i=3; i < 10000; ++i)
		counter += std::all_of(a, a+3, [i] (int j) {return i%j > 2 && i%j < j-2;});
	std::cout << counter;
}
