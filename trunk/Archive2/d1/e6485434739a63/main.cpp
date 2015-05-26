#include <iostream>
#include <string>
#include <vector>

class father {};

class son : public father {};

class son2 : public son {};

int main()
{
    father f1, f2;
    son s1;
    son2 s2;
    
    std::vector<father> v;
    v.push_back(f1);
    v.push_back(f2);
    v.push_back(s1);
    v.push_back(s2);
    
    return 0;
}
