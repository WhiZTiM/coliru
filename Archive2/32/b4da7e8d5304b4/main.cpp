#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>



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
   std::map<std::pair<std::string, int>, std::vector<std::string> > my_map;
   std::cout << "size before insert: " << my_map.size() << "\n";
   
   std::vector<std::string> v;
   v.push_back("abcde"); 
   my_map.insert(std::make_pair(std::make_pair("aaa",1),v));
   
   std::cout << "size after insert: " << my_map.size() << '\n';
}