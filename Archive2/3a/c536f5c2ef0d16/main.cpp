#include <iostream>
#include <ostream>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;

int main()
{
    std::string line;
	std::string one = "one";
	std::string three = "three";
	std::string five = "five";

	std::chrono::high_resolution_clock timer;
	auto start = timer.now();
	for (int i = 0; i < 100000; i++)
	{
		line = one + "two" + three + "four" + five;
	}
	auto end = timer.now();
	auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	std::cout << "Using line = var + var for 100000 iterations time is: " << diff << std::endl;
	
	start = timer.now();
	for (int i = 0; i < 100000; i++)
	{
		line += one;
		line += "two";
		line += three;
		line += "four";
		line +=five;
	}
	end = timer.now();
	diff = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	std::cout << "Using line += var; line += var for 100000 iterations time is: " << diff << std::endl;

	cin.get();
	return 0;
}