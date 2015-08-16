#include <cstring>
#include <iostream>
 
int main() 
{
    char input[100] = "Hello. How are you? Are you coming today?";
    char *token = std::strtok(input, ".?");
    while (token != NULL) {
        std::cout << token << '\n';
        token = std::strtok(NULL, ".?");
    }
return 0;
}