#include <iostream>

template<typename T>
using alias = T;

struct stuff
{
    stuff() = default;

	int raw_data[3] = { 1,2,3 };
	
	alias<int[3]>& get()
	{
		return raw_data;
	}

	operator alias<int[3]>& ()
	{
		return raw_data;
	}
};

int main()
{
	stuff s;

	int crap[3] = { 0 };
	//crap += 99;    //error C2106: '+=': left operand must be l-value
	//s.get() += 99; //error C2106: '+=': left operand must be l-value
	s += 99;       //uses conversion to int[3] ref, then...adds 99 to the first element. WTF?

	std::cout << s.raw_data[0] << "\n";
	std::cout << s.raw_data[1] << "\n";
	std::cout << s.raw_data[2] << "\n";

}
