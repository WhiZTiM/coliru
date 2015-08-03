#include <iostream>
#include <string>
#include <vector>
#include <limits>

int main()
{
const int b= std::numeric_limits<int>::max() - 16; // just an example for a const value
const int c=b-2000; // just an example as well
// a lot of lines later, in a different file entirely
for (int i=0;i<100;++i){
  int k=i+(b-c); // OK, no problem!
  int kk=i+b-c; // will cause this loop to become an infinite loop! But only in -O3
  // do something with k or kk
  std::cerr << k << std::endl;
  std::cerr << kk << std::endl;
}
}
