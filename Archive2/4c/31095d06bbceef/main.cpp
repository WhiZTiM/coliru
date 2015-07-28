#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
 
int main()
{
    std::vector<std::string> vec{ "Dortmunder Actien-Brauerei" };
    
    // &, =
    
    auto push_to_vec = [](const std::string& beer)
    {
        vec.push_back(beer);
    };
    
    for (const auto& b : { "Hansa", "Bergmann", "Thier" })
    {
        push_to_vec(b);
    }
    
    for (const auto& b : vec) std::cout << b << '\n';
}