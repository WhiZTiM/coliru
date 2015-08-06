#include <iostream>
#include <stdio.h>
#include <vector>
#include <memory>

using namespace std;

class A
{
public:
  A(unique_ptr<vector<int>>&& a);
  void additem(int c);
  unique_ptr<vector<int>> return_data();
private:
  unique_ptr<vector<int>> d;
};

A::A(unique_ptr<vector<int>>&& a) : 
  d(forward<unique_ptr<vector<int>>>(a))
{}

void A::additem(int c)
{
  d->push_back(c);
}

unique_ptr<vector<int>> A::return_data()
{
  return move(d);
}

int main()
{
  unique_ptr<vector<int>> test = make_unique<vector<int>>();;

  for (int i = 0; i<10; i++)
  {
    test->push_back(i);
  }
  cout << test->size() << endl;
  A a(move(test));
  a.additem(10);
  test = a.return_data();
  cout << test->size() << endl;
}