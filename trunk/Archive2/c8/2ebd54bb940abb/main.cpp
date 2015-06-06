#include <set>
#include <map>
#include <utility>
#include <cassert>
#include <iostream>

int main()
{
    std::set<int> s;
    std::map<int, int> m;
    
    const auto firstSetInsertResult = s.insert(2);
    const auto firstMapInsertResult = m.insert(std::make_pair(2, 4));
    
    try
    {
        const auto secondSetInsertResult = s.insert(2);
        const auto secondMapInsertResult = m.insert(std::make_pair(2, 5));
        
         std::cout << "nah, doesn't throw" << std::endl;
         
         assert(firstSetInsertResult.second && !secondSetInsertResult.second);
         assert(firstMapInsertResult.second && !secondMapInsertResult.second);
         
         assert(firstSetInsertResult.first == secondSetInsertResult.first);
         assert(firstMapInsertResult.first == secondMapInsertResult.first);
         
         assert(secondMapInsertResult.first->second == 4);
         
         std::cout << "and Andrea writes stuff on StackOverflow :P" << std::endl;
    }
    catch (const std::exception&)
    {
        std::cout << "does throw" << std::endl;
    }
}
