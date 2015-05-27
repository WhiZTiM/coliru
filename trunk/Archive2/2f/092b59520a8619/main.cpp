#include <iostream>

static constexpr const char elecSigTypeEnum[] = {
    		'x',
			'y',
			'z'
	};

int main()
{
    std::cout << sizeof(elecSigTypeEnum) << std::endl;
}
