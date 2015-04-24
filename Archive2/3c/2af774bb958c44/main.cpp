#include <iostream>
#include <sstream>

class Logger : public std::ostringstream
{
public:
    ~Logger()
	{
		std::cout << this->str() << std::endl;
	}

	Logger& stream()
	{
		return *this;
	}
};

int main( int argc, char ** argv )
{
	// 1. 
	// Prints an address, e.g. 0x106e89d5c.
	Logger() << "foo";

	// 2. 
	// Works as expected.
	Logger().stream() << "foo";

	// What is the difference between 1. and 2.?

	return 0;
}
