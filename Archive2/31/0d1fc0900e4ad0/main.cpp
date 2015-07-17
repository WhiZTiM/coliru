#include <iostream>
#include <string>
#include <cctype>

int main(int argc, char* argv[])
{
    int uppercaseCounter = 0;
    std::string password = "PassWord";
    for (auto& e : password)
    {
        if (std::isupper(e))
            uppercaseCounter++;
    }
    std::cout << uppercaseCounter;
}