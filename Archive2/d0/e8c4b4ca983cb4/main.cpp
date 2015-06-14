#include <iostream>
#include <ostream>

struct B
{
    virtual void g() { std::cout << "B::g()" << std::endl; }
};

class D1 : virtual public B
{
    // Ésta es la sobrecarga más cercana.
    void g() { std::cout << "D1::g()" << std::endl; }
};

class D2 : virtual public B {};

class D3 : public D1, public D2
{
    // Como D1::g() es la sobrecarga más cercana (recuerda que solo puede haber una),
    // es la que hereda D3 (y es privada).
};

int main()
{
    D3 d;
    B* pb = &d;
    
    // d.g(); Error, D1::g es privado.
    
    // Sin embargo, D1::g() se ejecuta sin problemas, ya que yo estoy
    // llamando a B::g(), que es público (aunque luego, al ser virtual, ejecuta
    // la de D1). Que algo sea privado (o protegido desde el punto de vista de los
    // usuarios de la jerarquía), significa que no se puede "llamar explícitamente" (jamás
    // podré escribir el nombre de un miembro privado de otro), pero no significa que no pueda
    // ejecutarse (como por ejemplo, con sobrecarga virtual). Recuerda, en ésta llamada:
    //   A) Estoy llamando a B::g() (público), pero B::g() no es quién se ejecuta (por que es virtual).
    //   B) NO estoy llamando a D1::g(), (privado), porque no es lo que yo he escrito, pero D1::g() es quién se ejecuta (por que es virtual).
    pb->g();
}