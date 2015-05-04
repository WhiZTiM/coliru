#include <iostream>
 
using namespace std;

#define POW(a) a * a

inline int pow(int a) { return a * a; }

int main()
{
   int a = 3;
   
   // cout << POW(a + 1) << endl;
   // cout << pow(a + 1) << endl;
   
   return 0;
}
