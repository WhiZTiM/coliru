#include <iostream>
#include <string>
#include <vector>

#include <regex>

int main()
{
    std::string s = "/storage/emulated/0/Android/data/com.ncr.cxp.client.products.reference/files/bootloader";
    std::regex expr("/storage/emulated/.+");
    
    if (regex_match(s, expr)) std::cout<<"yes\n";
    
    
}
