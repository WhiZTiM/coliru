#include <iostream>
#include <vector>

using namespace std;

int main()
{
    std::vector<int> IntVect;
    IntVect.push_back(10);
    int* pInt = &IntVect[0];
    cout << *pInt << "\n";  // ok
    IntVect.push_back(20);
    cout << *pInt;  // problem here
}
