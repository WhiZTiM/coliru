#include <iostream>

int main()
{
    std::cout << R"?!(Non ! Oui ? Pourquoi "()" ?)?!" << std::endl;
    std::cout << "12.0 / 5 = " << 12.0 / 5.0 << std::endl;
    std::cout << "12 / 5 = " << 12 / 5 << std::endl;

    std::cout << "Le nombre 666 en base 8 (octale) : " << std::oct << 666 << std::endl;
    std::cout << "En base 16 (hexadécimal) : " << std::hex << 666 << std::endl;
    std::cout << "Et en base 10 (décimal) : " << std::dec << 666 << std::endl;
    
    std::cout << "Et maintenant, en affichant les bases !" << std::endl;
    std::cout << std::showbase;
    std::cout << "Le nombre 5479 ==> " << std::oct << 5'479 << std::endl;
    std::cout << "5479 ==> " << std::hex << 5'479 << std::endl;
    std::cout << "5479 ==> " << std::dec << 5'479 << std::endl;
    std::cout << std::noshowbase << std::endl;
    
    std::cout << "Passons aux conversions !" << std::endl << std::endl;
    
    std::cout << "Prenons le nombre 1203 par exemple..." << std::endl;
    std::cout << "1203 correspond à ";
    std::cout << std::hex << (1203 / 16) / 16 << (1203 / 16) % 16 << 1203 % 16 ;
    std::cout << " en hexadécimal" << std::endl << std::endl;
    
    std::cout << "Prenons un autre exemple, 355" << std::endl;
    std::cout << "355 correspond à ";
    std::cout << std::oct << (355 / 8) / 8 << (355 / 8) % 8 << 355 % 8;
    std::cout << " en octal" << std::endl << std::endl;
}
