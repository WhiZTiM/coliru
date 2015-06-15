#include <iostream>
#include <ostream>

// Incluso sin parámetros de función, solo de plantilla.
// En éste caso, la instanciación implícita con <tipo> es obligatoria.
template<typename T>
void imprimir_valor_por_defecto_de()
{
    // El tipo T debe ser `default constructible` (que tenga constructor por defecto).
    std::cout << T() << std::endl;
}

struct A
{
    A(int) {} // Constructor que recibe un entero (el constructor por defecto se borra).
};

int main()
{
   imprimir_valor_por_defecto_de<int>();
   imprimir_valor_por_defecto_de<float>();
   
   // A no es `default constructible` (el constructor por defecto de A ha sido eliminado por A::A(int)
   // imprimir_valor_por_defecto_de<A>(); // Error de instanciación.
}