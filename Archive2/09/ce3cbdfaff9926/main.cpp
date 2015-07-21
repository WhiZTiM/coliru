#include <iostream>
using namespace std;

void f (const int& i)
{
  cout << "in const reference function";
}
void f ( int &i)
{
  cout << "in non const reference function";
}
int main()
{
    int i;
    f(3);
    f(i);
}