#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

int main()
{
    using in=istream_iterator<int>;
    vector<int> v{in{cin}, in{}};
    for (auto x:v)
    {
     	 cout << x <<", ";
    }
}