#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class ValueWrapper {
public:
    ValueWrapper(char val) : v(val) {}
    bool in(std::vector<char>& vec) {
        return std::find(vec.begin(), vec.end(), v) != vec.end();
    }
private:
    char v;
};

using is = ValueWrapper;

int main()
{
    std::vector<char> vec = {'A', 'B', 'C'};
    
    if ( is('B').in(vec) )
        std::cout << "yes";
    else
        std::cout << "no";
}
