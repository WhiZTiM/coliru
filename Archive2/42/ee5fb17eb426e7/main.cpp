#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    std::vector<int> foo = std::vector<int>();

    foo.push_back(0);
    foo.push_back(11);
    foo.push_back(222);
    foo.push_back(3333);

    std::stack<int> bar = std::stack<int>();

    cout << endl << foo.size() << endl << endl;

    return 0;
}