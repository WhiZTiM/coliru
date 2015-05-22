#include <iostream>
#include <sstream>
#include <map>

int main()
{
    // in global space 
    int v[50000];
    
    std::stringstream ss("3 1 2 3"); // fake input
    
    // in a function
    int n;
    ss >> n;
    for(int i(0); i < n; ++i)
        ss >> v[i];
    
    std::map<int, int, std::greater<int>> m;
    for(int i(n-1); i > -1; --i){
        auto it(m.find(m[v[i]]));
        if(it == std::end(m)){
            m.insert({m[v[i]], i});
        }
    }
    std::cout << "map : \n";
    for(auto &x: m)
        std::cout << x.first << ' ' << x.second << '\n';
}