#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <time.h>
#include <ctime>

 
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


int main(void)
{
    time_t epoch = 1431087129;
    
    printf("%ld seconds since the epoch began\n", (long)epoch);
    printf("%s", asctime(gmtime(&epoch)));
    
    std::tm tm = *std::localtime(&epoch);

    char mbstr[100];
	if (std::strftime(mbstr, sizeof(mbstr), "%A %c", &tm)) {
		std::cout << mbstr << '\n';
	}
}

