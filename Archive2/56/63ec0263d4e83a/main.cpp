#include <iostream>
#include <string>
#include <vector>
#include <cstring>

template<size_t N>
void copyStringToArray(char (&arr)[N], const char* str)
{
    strncpy(&arr, str, N);
}

int main()
{
    static const char* const str = "Hello, world!";
    char arr[25];

    std::cout << "Attempting to copy string '" << str << "' into character array. Size of string: " << strlen(str) << "; Size of character array: " << sizeof(arr) / sizeof(char) << std::endl;
    std::cout << "Character array currently contains: '" << arr << "'" << std::endl;
    //copyStringToArray

    return 0;
}
