#include <string>
using std::string;
#include <map>
using std::map;
#include <utility>
using std::pair;

#include <iostream>

struct bond { int i; };

class Account
{
    map<bond, int> bonds;

public:
    void checkBondsAndUpdate()
    {
        for(auto &it1 : bonds)
        {
            bond bond =  it1.first;
            std::cout << bond.i;
        }
    }
};

int main()
{
}
