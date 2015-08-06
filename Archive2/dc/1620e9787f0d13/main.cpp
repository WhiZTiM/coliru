#include <valarray>
#include <iostream>    

using namespace std;

int main()
{
  valarray<int> v0(2, 4);
  valarray<int> v1;
  v1 = v0;
  cout << "v0.size: " << v0.size() << endl;
  cout << "v1.size: " << v1.size() << endl;
  cout << "v0[0]: " << v0[0] << endl;
  cout << "v1[0]: " << v1[0] << endl;
}
