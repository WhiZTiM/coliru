#include <iostream>
#include <utility>

using namespace std;

class A
{
public:
    A(size_t i = 10) : u_tam(i), p_vec(new int[u_tam])
    {
        // size_t: tipo pensado para trabajar con memoria (índices y tamaños de vectores).
        for (size_t idx = 0; idx < u_tam; ++idx)
            p_vec[idx] = 0;
    }
    
    // No recibe por copia porque o si no la definición sería recursiva,
    // Si reciviera una referencia no constante, no podría copiar de objetos constantes.
    A(A const& he) : u_tam(he.u_tam), p_vec(new int[u_tam])
    {
        for (size_t idx = 0; idx < u_tam; ++idx)
           p_vec[idx] = he.p_vec[idx];
    }
    
    // Hacemos un robo de recursos porque sabemos que ese objeto
    // va a ser destruido pronto.
    A(A&& he) : u_tam(he.u_tam), p_vec(he.p_vec)
    {
        he.p_vec = nullptr;
        he.u_tam = 0;
    }
    
    ~A()
    {
        delete[] p_vec;
    }
    
    unsigned tam() const { return u_tam; }

    // Recibe una referencia constante para que los objetos constantes puedan asignarse a int.
    // Devuelve una referencia por si quieres pasar el objeto, tras la asignación, a otra función.
    //   P.e: f(a = b);
    A& operator=(A const& he)
    {
        // Evitar autoasignacion.
        if (this == &he)
            return *this;
        
        // Ahorramos destrucción si los tamaños son iguales.
        if (u_tam != he.u_tam) {
            delete[] p_vec;
            u_tam = he.u_tam;
            p_vec = new int[u_tam]; // Riesgo de falta de memoria (objeto en estado inválido).
        }
        
        for (size_t idx = 0; idx < u_tam; ++idx)
            p_vec[idx] = a.p_vec[idx];
    }
    
/*
    A& operator=(A a) // copy-and-swap idiom
    {
        // El paso es por copia, para evitar que, si no queda memoria, la excepción
        // se lance durante la creación de `a`, y no afecte a `this` (exception safe).
        
        // Además, me evito la pesada comprobación anti auto-asignación.
        
        // Además, la "copia" de un objeto ya se hace en el constructor de copia (el for), así que,
        // pasando por copia, reutilizamos ese código.
        
        // Le paso mis recursos para que el destructor del objeto temporal haga el trabajo por mí.
        swap(u_tam, a.u_tam);
        swap(p_vec, a.p_vec);
    }
*/

    A& operator=(A&& a)
    {
        // Le paso mis recursos, para que `a` los destruya, ya que es un objeto temporal.
        swap(u_tam, a.u_tam);
        swap(p_vec, a.p_vec);
    }
    
    // El operator[] está pensado para que sea "muy rápido".
    // No hay comprobación de rango.
    int& operator[](size_t idx)
    { return p_vec[idx]; }
    
    // Devuelve int en vez de const int&, ya que en memoria ocupan lo mismo
    // (las referencias se utilizan para evitar copias).
    int operator[](size_t idx) const
    { return p_vec[idx]; }
    
    // Versión segura con comprobación de rango.
    int& at(size_t idx)
    {
        if (idx >= u_tam)
            throw asdasdasd;
            
        return p_vec[idx];
    }
    
    int at(size_t idx) const
    {
        if (idx >= u_tam)
            throw asdasdasd;
            
        return p_vec[idx];
    }
    
private:
    const size_t u_tam;
    int* p_vec;
};


int main()
{
   A a;

   return 0;
}
