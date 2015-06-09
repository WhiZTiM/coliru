#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
   vector<int> dst;
   vector<int> v1{ 1,2,4,6 };
   vector<int> v2{ 3,5,7 };
   merge(begin(v1), end(v1), begin(v2), end(v2), back_inserter(dst));
   
   for (int i = 0; i < dst.size();i++)
      cout << dst[i] << "\n";
}
