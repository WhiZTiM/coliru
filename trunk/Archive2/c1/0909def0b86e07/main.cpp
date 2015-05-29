#include <list>
#include <algorithm>
#include <iostream>
#include <chrono>
using namespace std;
int main(int argc, char* argv[])
{

    
	list<int> listInt(20000000, 0);
	int i = 0;
	for (int& nb : listInt){
		nb = i;
		i++;
	}

	auto s = std::chrono::high_resolution_clock::now();
	//listInt.erase(std::remove_if(listInt.begin(), listInt.end(), [](int x){return (x % 2) == 1; }), listInt.end()); //4 second 
	listInt.remove_if([](int x){return (x % 2) == 1; });// 17 second 

	auto e = std::chrono::high_resolution_clock::now();

	cout.precision(5);
	cout << std::chrono::duration_cast<std::chrono::milliseconds>(e-s).count() <<endl;

	return 0;
}