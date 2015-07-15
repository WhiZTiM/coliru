#include <iostream>
#include <functional>

using namespace std;

template <typename RetType, typename... ArgTypes>
RetType q(int& s, function<RetType(ArgTypes...)> f, ArgTypes... args)
{
    auto result = f(args...);

	s = 5;
	
	return result;
}

int h(int a, int b, int c) { return a + b + c; }

int main()
{
	int s;
	q(s, h, 1, 2, 3);
    
    cout << "Ok";

	return 0;
}