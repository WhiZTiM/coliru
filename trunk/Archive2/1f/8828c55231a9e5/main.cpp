#include <iostream>
#include <string.h>

#define FILE_ "filename\0\0\0\0\0\0\0\0"

int main() {
    std::cout << sizeof(FILE_)-1 << " " << strlen(FILE_);
}