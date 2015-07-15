#include <iostream>

int main() {
    /*
        Programme sous license creative common.
        De Haitham Mekhaemar, mahtiah@hotmail.fr
        Description : 
        Simple programme qui affiche un message à l'écran,
        les options de compilations sont personnalisées,
        Dernière modification effectuée le : 15/07/2015 à 16:26
    */
    
    auto nombre = { 5, 0, 6, 5 };
    
    for(int i=0; i < 4; i++) {
        std::cout << nombre[i] << std::endl;
    }
    
    std::cout << "Hello, world !" << std::endl;
    
    std::cout << 576'489'577 << std::endl;
    std::cout << std::hex << std::showbase;
    std::cout << 0xA - 0x9 << std::endl;
    std::cout << std::dec << std::noshowbase;
    std::cout << 5 - (2+3) / 4 << std::endl;
    
    std::cout << std::showbase;
    std::cout << 66 << " ==> " << std::hex << 66 << std::endl; 
    
    std::cout << std::dec << std::boolalpha;
    std::cout << "0xA == 10 ? " << (0xA == 10) << std::endl;
    
	return 0;
}
