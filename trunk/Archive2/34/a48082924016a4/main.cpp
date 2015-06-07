
#include <sys/epoll.h>
#include <string>
#include <iostream>

int main() {
    uint16_t i = 12;
	char temp[2] = i;
	uint16_t j = temp;

	std::cout << j << '\n';

	return 0;
}

