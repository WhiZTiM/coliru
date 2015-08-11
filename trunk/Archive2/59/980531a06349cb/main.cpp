#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

std::vector<std::vector<int>> print_subsets(std::vector<int> &x, int l)
{
    
    if(l==x.size()-1)
    {
        std::vector<int> temp = {x.at(l)};
        std::vector<std::vector<int>> temp2;
        temp2.push_back(temp);
        return temp2;
    }
    
    auto p = print_subsets(x,l+1);
    std::vector<std::vector<int>> g;
    for(auto ele : p)
    {
        ele.push_back(x.at(l));
        g.push_back(ele);
    }
    p.insert(p.end(),g.begin(),g.end());
    std::vector<int> temp = {x.at(l)};
    p.push_back(temp);
    
    return p;
    
}

int main()
{
   
   std::vector<int> x = {1,2,3};
   auto sol = print_subsets(x,0);
   for(auto ele : sol)
    std::cout<<ele<<std::endl;
}
