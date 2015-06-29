#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void printDebug(vector <int>  ar)
{
    for (auto it = ar.begin(); it != ar.end(); it++)
    {
        vector <int>::iterator end = ar.end() - it;
        for (auto yt = ar.begin(); yt != end; yt++)
        {
            cout << *it << " : " << end;
        }
        cout << endl;
    }
}



int main () {
    std::map<std::string, std::vector<std::string>> myMap;

    std::vector<string> vec1 = {"11", "22", "33"};
    std::vector<string> vec2 = {"44", "55"};
    std::vector<string> vec3 = {};
    
    std::string key1 = "1";
    std::string key2 = "2";
    std::string key3 = "3";
    
    myMap.insert(std::make_pair(key1, vec1));
    myMap.insert(std::make_pair(key2, vec2));
    myMap.insert(std::make_pair(key3, vec3));
    
    auto lookup = "55";
    auto it = std::find_if(
        std::begin(myMap),
        std::end(myMap),
        [&](auto& p ) 
        { 
            return std::find(std::begin(p.second), std::end(p.second), lookup) != std::end(p.second);
        } 
        );
    
    if(it != std::end(myMap))
        std::cout << it->first;
    else
        std::cout << "not found";
}