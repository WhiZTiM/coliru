#include <iostream>
#include <initializer_list>

using namespace std;

class Punto
{
public:
    Punto(double x = 0., double y = 0.) : d_x(x), d_y(y)
    {}
    
    Punto(std::initializer_list<double> const& v)
        : d_x(*v.begin()), d_y(*(v.begin() + 1))
    {}
    
    double& x() { return d_x; }
    double& y() { return d_y; }
    
    double x() const { return d_x; }
    double y() const { return d_y; }
    
    Punto& operator*=(double d)
    {
        d_x *= d;
        d_y *= d;
        
        return *this;
    }
    
    Punto operator-() const { return Punto(*this) *= -1; }
    Punto& operator++() { return *this += 1; }
    
    Punto& operator+=(const Punto& p)
    {
        d_x += p.d_x;
        d_y += p.d_y;
        
        return *this;
    }
    
    Punto operator++(int)
    {
        Punto r(*this);
        
        (void)++*this;
        
        return r;
    }
    
    // Operadores de conversión siempre devuelven por valor: construir y devolver
    // un nuevo valor basado en el valor de *this.
    operator pair<double, double>() const
    {
        return {d_x, d_y};
        
        // return make_pair(d_x, d_y);
    }
    
private:
    double d_x, d_y;
};

template<typename T>
class Vector
{
public:
    using iterator = T*;
    
    Vector(size_t tam, T const& def = T()) : u_tam(tam), p_v(new T[u_tam])
    {
        for (size_t idx = 0; idx < u_tam; ++idx)
            p_v[idx] = def;
    }
    
    Vector(std::initializer_list<double> const& l) : u_tam(l.size()), p_v(new T[u_tam])
    {
        T* it = begin();
        
        for (std::initializer_list<double>::iterator i = l.begin(); i != l.end(); ++i, ++it)
            *it = *i;
            
        /*
        for (auto i = l.begin(); i != l.end(); ++i, ++it)
            *it = *i;
            
        for (auto& o : l) {
            *it = o;
            ++it;
        }
        
        std::copy(l.begin(), l.end(), begin());
        */
    }
    
    iterator begin() const { return p_v; }
    iterator end() const { return p_v + u_tam; }
    
    size_t tam() const { return u_tam; }
    
    T& operator[](size_t idx) { return p_v[idx]; }
    T const& operator[](size_t idx) const { return p_v[idx]; }
    
private:
    size_t u_tam;
    T* p_v;
};

Vector<int> aVector()
{
    return {1, 5, 2, 4, 3};
}

ostream& operator<<(ostream& os, Vector<int> const& v)
{
    os << "(";
    
    for (size_t idx = 0; idx < v.tam(); ++idx)
        os << v[idx] << ", ";
        
    /*
    for (Vector<int>::iterator i = v.begin(); i != v.end(); ++i)
        os << *i << ", ";
        
    for (auto i = v.begin(); i != v.end(); ++i)
        os << *i << ", ";
        
    for (auto& o : v)
        os << o << ", ";
        
    // Lo de arriba es exáctamente equivalente a:
    
    for (auto i = v.begin(); i != v.end(); ++i) {
        auto& o = *it;
        
        cout << o << endl;
    }
    
    // Como las listas de inicialización también tienen definido begin() y end():
    
    for (auto& o : {1, 2, 3, 4, 5})
        cout << o << endl;
        
    */
        
    os << ")";
        
    return os;
}

int main()
{   
    Vector<int> v = aVector();
    Punto p(3., 2.5);
    std::pair<double, double> par = p;
    
    cout << v << endl;
    cout << par.first << ", " << par.second << endl;
    
    return 0;
}


