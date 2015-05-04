#include <iostream>

int main() {
    //Many places can handle Unicode literals in code.
    //Many places can handle Unicode characters at the console.
    //Others...
    std::cout << "123会意字 / 會意字" << std::endl;
    
    //Try not to mix std::wcout and std::cout.
    std::wcout << u8"会意字 / 會意字" << std::endl;
    return 0;
}