#include <iostream>
#include <string>
#include <set>

int main()
{
    std::string http_code{"401"};
    
    static std::set<std::string> bad_codes{"400", "409", "206"};
    if (bad_codes.find(http_code) == bad_codes.end())
    {
        std::cout << "No bad code detected\n";
    }
    else
    {
        std::cout << "Bad code detected\n";
    }
}
