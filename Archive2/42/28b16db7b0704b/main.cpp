#include <iostream>
#include <utility>

using namespace std;

struct Pos { long double x = 0.0, y = 0.0, z = 0.0; };

class Atomos
{
public:
    Atomos(size_t num = 30000000) : u_num(num), v_atomos(new Pos[u_num])
    {}

    Atomos(Atomos const& atomos);
    Atomos(Atomos&& atomos);
    ~Atomos() { if (v_atomos) delete[] v_atomos; }

    Atomos& operator=(Atomos const& atomos);

    Pos& operator[](unsigned i) { return v_atomos[i]; }
    Pos operator[](unsigned i) const { return v_atomos[i]; }

private:
    size_t u_num;
    Pos* v_atomos;
};

Atomos::Atomos(Atomos const& atomos)
    : u_num(atomos.u_num), v_atomos(new Pos[u_num])
{
    cout << "Copiando..." << endl;

    for (unsigned i = 0; i < u_num; ++i)
        v_atomos[i] = atomos.v_atomos[i];
}

Atomos::Atomos(Atomos&& atomos)
    : u_num(atomos.u_num), v_atomos(atomos.v_atomos)
{
    cout << "Moviendo..." << endl;

    atomos.v_atomos = nullptr;
}

Atomos& Atomos::operator=(Atomos const& atomos)
{
    if (this == &atomos)
        return *this;

    if (u_num != atomos.u_num) {
        delete[] v_atomos;
        u_num = atomos.u_num;
        v_atomos = new Pos[u_num];
    }

    for (unsigned i = 0; i < u_num; ++i)
        v_atomos[i] = atomos.v_atomos[i];

    return *this;
}

class AtomosPrinter
{
public:
    AtomosPrinter(Atomos const& atomos) : o_atomos(atomos) {}
    AtomosPrinter(Atomos&& atomos) : o_atomos(move(atomos)) {}

    void print(unsigned cuantos)
    {
        for (unsigned i = 0; i < cuantos; ++i)
            cout << "("
                 << o_atomos[i].x << ", "
                 << o_atomos[i].y << ", "
                 << o_atomos[i].z << ") ";

        cout << endl;
    }

private:
    Atomos o_atomos;
};

AtomosPrinter CrearPrinter(Atomos&& atomos)
{
    AtomosPrinter printer(move(atomos));

    return printer;
}

AtomosPrinter InicializarAtomosYCrearPrinter(Atomos&& a)
{
    a[3].x = 4.5;
    a[5].z = 6.7;

    return CrearPrinter(move(a));
}

int main()
{
    AtomosPrinter printer = InicializarAtomosYCrearPrinter(Atomos());

    printer.print(10);

    return 0;
}
