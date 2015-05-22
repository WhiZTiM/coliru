#include <iostream>
using namespace std;

int main()
{
  int A[] = {1, 2, 3, 4, 5, 6};
  for (int current : A)
    cout << current << endl;
  cout << "done" << endl;
  return 0;
}