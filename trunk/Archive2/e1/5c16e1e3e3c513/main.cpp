#include <iostream>
#include <string>
 
int main()
{
    std::string input(" ALL GLItters are not gold");
    char a;
    std::cin >> a;
    for (char& c : input)
    {
        if (c == a)
            c = 'g';
    }
    std::cout<<"\n" << input << std::endl;
 }