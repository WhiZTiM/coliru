#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

map<char, int> get_counts(string const & line)
{
    map<char, int> m;
    for (auto iter = begin(line); iter != end(line); ++iter)
    {
        if (m.count(*iter))
        {
            m[*iter]++;
        }
        
        else
        {
            m[*iter] = 1;    
        }
    }
    
    return m;
}

string uniqs(string const & line)
{
    auto m = get_counts(line);
    string s = "";
    for (auto iter = begin(line); iter != end(line); ++iter)
    {
        if (m[*iter] == 1) s += *iter;
    }
    
    return s;
        
}

int main()
{
    auto sample = string("mississippi river");
    cout << "Before: " << sample << endl;
    cout << "After : " << uniqs(sample) << endl;
}
