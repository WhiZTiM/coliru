#include<map>
#include<iostream>
#include<string>
int main()
{
    std::multimap<std::string,int> word;
    std::string key="with";
    
    word.insert(std::pair<std::string,int>(key,16));
    word.insert(std::pair<std::string,int>(key,6));
    word.insert(std::pair<std::string,int>(key,15));
    
    word.emplace("with",16);
    word.emplace("with",6);
    word.emplace("with",15);
   
    
    for( auto &x : word)
      std::cout<<x.first<<" " << x.second<<"\n";    
    
}