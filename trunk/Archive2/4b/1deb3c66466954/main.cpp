#include <iostream>
#include <string>
#include <vector>

using namespace std;

void f(int& i)
{
    cout << "&" << i;// = i + 1;
}

void f(int&& i)
{
    cout << "&&" <<  i;// = i + 1;
}

int main()
{
   vector<int> ii = { 1, 2, 3 };
   for (auto&& i : ii)
    i = i + 1;
   for (auto&& i : ii)
     cout << i << endl; 
   int z = 8;
   f(z);
   int&& zz = z + 1;
   f(zz);
   
   return 0;
}


