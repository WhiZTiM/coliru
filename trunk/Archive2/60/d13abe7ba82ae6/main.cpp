#include <iostream>
#include <numeric>
#include <vector>

int main()
{
	const int orig_size = 66;
	const float skip_ratio = .6;
	const int new_size = skip_ratio * orig_size;
    
    std::cout << "orig_size: " << orig_size << '\n';
	std::cout << "new_size: " << new_size << '\n';
	
	const int p = new_size * 2;
	const int n = orig_size * 2;
	int d = p - orig_size;
	for (int i = 0; i < orig_size; ++i) {
        if (d >= 0) {
            std::cout << i << ' ';
            d -= n;
        }
        d += p;
    }
	std::cout << std::endl;
	
	return 0;
}
