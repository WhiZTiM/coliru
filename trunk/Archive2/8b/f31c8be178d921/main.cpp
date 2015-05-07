#include <iostream>
 
using namespace std;

struct A { int i = 0; };

void z(A& a) { cout << 1 << endl; }
void z(A const& a) { cout << 2 << endl; }
void z(A&& a) { cout << 3 << endl; z(a); }

int main()
{
    z(A());
    
    // (1) ¿Qué imprime ésta expresión?
    // (2) Modifica las funciones pertinentes,
    //     con la mínima cantidad de cambios
    //     posibles, para que ésta expresión
    //     imprima 3333333.... (secuencia
    //     infinita de 3).
    
    return 0;
}
