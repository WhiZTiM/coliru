#include <iostream>
#include <string>
#include <functional>
 
int main()
{
    const std::string s = "Stand back! I've got jimmies!";
    std::hash<const std::string> hash_fn;
 
    size_t hash = hash_fn(s);
 
    std::cout << hash << '\n';
}