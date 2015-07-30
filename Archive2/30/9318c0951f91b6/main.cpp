#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    
    unordered_set<int> iset;
    iset.insert(123);
    iset.insert(234);
    for (const auto &t : iset)
        cout << t << endl;
        
    unordered_map<int, int> imap;
    imap[1] = 10;
    imap[2] = 20;
    for (const auto &t : imap)
        cout << t.first << "-->" << t.second << endl;
        
    for (auto it = imap.begin(); it != imap.end(); ++it) {
        it->second = 0;
    }

     for (const auto &t : imap)
        cout << t.first << "-->" << t.second << endl;
}
