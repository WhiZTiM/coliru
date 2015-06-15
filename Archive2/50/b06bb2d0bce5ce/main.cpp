#include <iostream>
#include <vector>
#include <memory>
#include <atomic>
using namespace std;

int main()
{
  atomic<int> i(10);
  cout << i << ++i << i++ << endl;


  return 0;
}