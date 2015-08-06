#include <iostream>

int main()
{
    std::cout << R"?!(Non ! Oui ? Pourquoi "()" ?)?!" << std::endl;
    std::cout << "12.0 / 5 = " << 12.0 / 5.0 << std::endl;
    std::cout << "12 / 5 = " << 12 / 5 << std::endl;
    
    int nombre = { 0 };
    
    std::cout << "Veuillez saisir un nombre : ";
    std::cin >> nombre;
    
    //std::cout << "Votre nombre en base 8 (octale) : " << std::oct << nombre << std::endl;
}
