#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

template<typename T>
struct PrintType;

int main()
{
	PrintType<decltype(throw "error")> a; 
}