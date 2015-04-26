#include <iostream>

int main() {
    
	long long l = 9223372036854775807ll;
	double d = l;
	int shift = 0;
	while(d == l)
	{
		++shift;
        d += shift;
	}
	std::cout << shift << std::endl;
	
	return 0;
}