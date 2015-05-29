#include <list>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;
int main(int argc, char* argv[])
{

    
	list<int> listInt(20000000, 0);
	int i = 0;
	for (int& nb : listInt){
		nb + i;
		i++;
	}

	time_t tbegin, tend;
	double texec = 0.;
	// Start timer
	tbegin = time(NULL);              // get the current calendar time


	std::remove_if(listInt.begin(), listInt.end(), [](int x){return (x % 2) == 1; }); //4 second 
	//listInt.remove_if([](int x){return (x % 2) == 1; });// 17 second 

	tend = time(NULL);                // get the current calendar time

	texec = difftime(tend, tbegin);    // tend-tbegin (result in second)
	cout.precision(5);
	cout <<fixed << texec<<endl;

	/*output on visual studio 2013 32bit 
		std::remove_if 4 second 
		listInt.remove_if 17 second

	output on visual studio 2013 64bit
		std::remove_if 1 second
		listInt.remove_if 7 second

	why : the std::remove_if use a forward iterator and the  listInt.remove_if use the list iterator (so the bidirectional iterator)
	forward iterator is faster than the bidirectional one , you can find more info on  http://www.cplusplus.com/reference/iterator/
	*/

	return 0;
}