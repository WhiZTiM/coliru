// g++ -o ex1 ex1.cc && ./ex1
 
#include <iostream>
 
using namespace std;
 
int myArray[] = {16, 2, 77, 40, 12071};
 
int n, result=0;
 
//=========================================
int main ()
{
 for ( n=0 ; n<3 ; ++n )
 {
  result += myArray[n];
 }
 cout << "Sum: " << result << endl ;
 return 0;
}