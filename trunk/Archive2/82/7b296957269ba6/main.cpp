#include <iostream>
#include <cstdint>

int main()
{
    // Cria a constante
    const uint32_t x = 5;
    
    // Acessa o endereço do x e guarda esse valor
    uint32_t* px = (uint32_t*)(&x);
    
    // Acessa o endereço pelo ponteiro e modifica o valor de x
    *px = 10;
    
    std::cout << (*(&x)) << std::endl;
}