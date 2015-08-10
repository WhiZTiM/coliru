#include <iostream>

using namespace std;

void g(int const& a)
{ cout << "g const&" << endl; }

void g(int& a)
{ cout << "g &" << endl; }

void g(int&& a)
{ cout << "g &&" << endl; }

int main()
{
   g(5);
   
   return 0;
}
