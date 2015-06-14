#include <iostream>
#include <ostream>

template<typename T>
void f(T t) { }

int main()
{
   f<float>(5); // Creo a la función f(float t), y la llamo con un entero. En ejecución, el entero se transforma en flotante antes de llamar.
}