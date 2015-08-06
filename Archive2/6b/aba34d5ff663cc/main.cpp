#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class A
{
public:
  A(vector<int> &a);
  void additem(int c);
private:
  vector<int>& d;
};

A::A(vector<int> &a) : d(a)
{
}

void A::additem(int c)
{
  d.push_back(c);
}

int main()
{
  vector<int> test;

  for (int i = 0; i<10; i++)
  {
    test.push_back(i);
  }
  cout << test.size() << endl;
  A a(test);
  a.additem(10);
  cout << test.size() << endl;
}