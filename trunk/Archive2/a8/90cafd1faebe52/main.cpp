#include <iostream>
#include <vector>
using namespace std;

template<class T>
void print(const T& t)
{
    cout << t;
}

template <class T>
void print(const vector<T>& t)
{
    cout << "[";
    for(auto const& elem : t)
    {
        print(elem);
        cout << " ";
    }
    cout << "]";
}

int main()
{
    vector<int> a;
    a.push_back(12);
    a.push_back(34);
    print(a);
    cout << "\n";
    vector<vector<int> > b;
    vector<int> b1;
    b1.push_back(1);
    b1.push_back(2);
    b.push_back(b1);

    vector<int> b2;
    b2.push_back(3);
    b2.push_back(4);
    b.push_back(b2);

    print(b);
    cout << "\n";
    return 0;
}