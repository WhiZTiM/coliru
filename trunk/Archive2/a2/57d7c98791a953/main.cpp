// g++ -o ex1 ex1.cc && ./ex1
 
#include <iostream>
 
using namespace std;
 
int myArray[] = {16, 2, 77, 40, 12071, 2};
 
int n, result=0;
 
//=========================================
int main ()
{
 for ( n=0 ; n<6 ; ++n )
 {
  result += myArray[n];
 }
 cout << "Sum: " << result << endl ;
 int sum = 0;
 for ( auto i : myArray){
      sum += i;
      }
      cout << "foo: " << sum << endl;
 return 0;
}