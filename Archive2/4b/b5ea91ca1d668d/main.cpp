#include <iostream>
#include <vector>
#include <memory>
using namespace std;

int main()
{
  vector<int> ar = {1};

  shared_ptr<int> sp(&ar[0]);

  cout<<*sp<<endl; // ---- [1]

  ar[0] = 10;

  cout<<*sp<<endl; // ---- [2]

  ar.clear();

  cout<<*sp<<endl; // ---- [3]



  return 0;
}