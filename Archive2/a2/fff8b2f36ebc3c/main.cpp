#include <iostream>
#include <algorithm>
#include <stack>
#include <unordered_map>

using namespace std;

int main()
{
    string s1 = "";
    stack<char> s;
    unordered_map<char, char> m;

    m.insert(std::make_pair('(', ')'));
    m.insert(std::make_pair('{', '}'));
    m.insert(std::make_pair('[', ']'));

    for (auto x : s1)
    {
        if (m.find(x) != m.end()) s.push(x);

        else 
        {
            auto it = m.find(s.top());
            if (s.empty() || (it->second) != x) { cout << "Invalid\n"; s.pop(); break; } 
        }

    }

}