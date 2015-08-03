#include <iostream>
using namespace std;

struct SM {
    int val;
    SM(int a) : val(a) { cout <<"Constructor val="<<a<<endl;}
    SM(const SM&) = delete;
    SM(SM&&) = delete;
    ~SM() { cout << "Destructor val="<<val<<endl; }
};

int main()
{
    SM sc[8] = { {0},{1},{2},{3},{4},{5},{6},{7} };
    return 0;
}