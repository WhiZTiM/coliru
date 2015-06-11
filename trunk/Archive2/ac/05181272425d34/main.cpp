#include<iostream>

#include<array>
using namespace std;

main()
{
array<int,3> first = {10, 20, 30};
array<int,3> second = {1, 2, 3};
first.swap(second);
for(int& x : first) std::cout<<' '<<x;

}