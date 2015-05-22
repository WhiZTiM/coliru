// g++ -o ex2 ex2.cc && ./ex2
 
#include <iostream>
 
using namespace std;
 
int myArray[] = {16, 2, 77, 40, 12071};
 
int n, result=0;
 
//=========================================
int main ()
{
 int arraySize = sizeof(myArray) / sizeof(int) ;
 cout << "Size: " << arraySize << endl ;
 
 for ( n=0 ; n<arraySize ; ++n )
 {
  result += myArray[n];
 }
 cout << "Sum: " << result << endl ;
 return 0;
}