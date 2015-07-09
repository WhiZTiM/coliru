#include <iostream>

enum Languages {HTML, CPP};

int main()
{
    std::cout << std::boolalpha;
    std::cout << "HTML différent de C++ : " << (Languages::HTML != Languages::CPP) << std::endl;
    std::cout << "C++ > HTML : " << (Languages::CPP > Languages::HTML) << std::endl;
}