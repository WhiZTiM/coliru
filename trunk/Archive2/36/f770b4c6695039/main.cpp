#include <iostream>

int main()
{
	const int orig_size = 66;
	const float skip_ratio = .6;
	const int new_size = skip_ratio * orig_size;
    
    std::cout << "orig_size: " << orig_size << "\n";
	std::cout << "new_size: " << new_size << "\n";
	
    const int a = orig_size * 2;
	const int b = new_size * 2;
	int c = b - orig_size;
	for (int i = 0; i < orig_size; ++i) {
        if (c >= 0) {
            std::cout << i << ' ';
            c -= a;
        }
        c += b;
    }
	std::cout << std::endl;
	
	return 0;
}
