
#include <iostream>
#include <algorithm>
#include <vector>
#include <memory>
#include <boost/bind.hpp>
using namespace std;


int foo(int a, int b)
{
    return a+b;
}

int main()
{
    vector<int> i;
    i.push_back(0);
    i.push_back(1);
    i.push_back(2);
    i.push_back(3);
    i.push_back(4);
    i.push_back(5);
    vector<int> b;
    transform(i.begin(), i.end(), back_inserter(b), boost::bind(&foo, _1, 1));
    for ( vector<int>::iterator k = b.begin(); k != b.end(); ++k)
    {
        cout<<*k<<endl;
    }
}
