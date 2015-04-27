#include <iostream>
#include <thread>
#include <unistd.h>

void inc(int * start)
{
    while(1)
	{
		*start++;
		usleep(1000);
	}
}

int main()
{
	int s = 0, start = 0;

	std::thread counter(inc, &start);

	while(s!=-1)
	{
		
		std::cout << "1. Set Num" << std::endl;
		std::cout << "2. Get Num" << std::endl;
		std::cout << "-1 Quit" << std::endl << ":";
		std::cin >> s;

		switch(s)
		{
			case 1:
				std::cout << "Num?:";
				std::cin >> start;
				break;
			case 2:
				std::cout << std::endl << "Number currenty:" << start << std::endl << std::endl;
		}
	}
}