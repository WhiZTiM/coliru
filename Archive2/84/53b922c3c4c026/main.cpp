#include <functional>
#include <iostream>
#include <cmath>
#include <vector>
 
int fibonacci(int number)
{
    if (number < 1 || number > 46)
    {
		return 0;
	}

	return number < 3 ? 1 : fibonacci(number - 1) + fibonacci(number - 2);
}

int centeredTriangular(int number)
{
    return (3*number*number + (3*number) + 2) / 2;
}

int powSum(int number, int exp)
{
    int sum = 0;
    for(int i=1; i<number; i++)
    {
        sum += std::pow(i, exp);
    }
    return sum;
}
 
int main()
{    
    std::vector<std::function<int(int)>> functions;
    if(true)
    {
        functions.push_back(fibonacci);
    }
    if(true)
    {
        functions.push_back([](int x) {return centeredTriangular(x);});   
    }
    if(true)
    {
        functions.push_back(std::bind(powSum, std::placeholders::_1, 2));
    }
    
    for(int i = 1; i<45; i++)
    {
        for(auto & func : functions)
        {
            std::cout << func(i) << " ";
        }
        std::cout << std::endl;
    }
}