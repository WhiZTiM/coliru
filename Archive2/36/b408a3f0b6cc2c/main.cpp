#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <iostream>


int main() {
    std::string a, b("foofoofoo"), c("barbarbar");
	
    std::vector<std::string> v;
    
    for (int i = 0; i < 1000000; ++i)
	{
	    v.push_back(b);
	}
    
	for (int count = 0; count < 5; ++count)
	{
		auto begin = std::chrono::high_resolution_clock::now();
		for (const auto & r : v)
		{
			a = r + c;
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> d = end - begin;

		std::cout << "operator+: " << d.count() << std::endl;

		begin = std::chrono::high_resolution_clock::now();
		for (const auto & r : v)
        {
			a = r;
			a += c;
		}
		end = std::chrono::high_resolution_clock::now();
		d = end - begin;
	
		std::cout << "operator+=: " << d.count() << std::endl;
	}

	return 0;
}