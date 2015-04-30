#include <vector>
#include <iostream>
using namespace std;

void func2(vector<int>&);
int func3(vector<int>&);
void func1()
{
    vector<int> IntV(0);

    func2(IntV);

    int x = func3(IntV);

    cout<<x;
}

void func2(vector<int>& IntV)
{
      IntV.push_back(1);
      IntV.push_back(2);
      IntV.push_back(3);
      IntV.push_back(4);
      IntV.push_back(5);
}

int func3(vector<int>& IntV)
{
    cout<<"IntV.size() - "<<IntV.size() << '\n'; //prints 5 - Okay
    vector<int>::iterator itr = IntV.begin();
    for(; itr != IntV.end(); itr++)
    {
        cout<<"Element - "<<*itr << '\n'; //prints 1 5 times
    }
    return 0;
}

int main()
{
    func1();
}
