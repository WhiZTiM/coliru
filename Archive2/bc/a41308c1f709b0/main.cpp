#include <iostream>

int main()
{
	const std::size_t orig_size = 66;
	const float skip_ratio = .6;
	const std::size_t new_size = skip_ratio * orig_size;
    
    std::cout << "orig_size: " << orig_size << "\n";
	std::cout << "new_size: " << new_size << "\n";
	
    const std::size_t a = orig_size * 2;
	const std::size_t b = new_size * 2;
	std::ptrdiff_t c = b - orig_size;
	for (std::size_t i = 0; i < orig_size; ++i) {
        if (c >= 0) {
            std::cout << i << ' ';
            c -= a;
        }
        c += b;
    }
	std::cout << std::endl;
	
	return 0;
}
