#include <initializer_list>
#include <iostream>
#include <stdexcept>

using namespace std;

class Vector
{
public:
    explicit Vector(size_t tam, double num = 0.0) noexcept
        : n(tam), datos(new double[n])
    {
        for (unsigned i = 0; i < n; ++i)
            datos[i] = num;
    }

    Vector(Vector const& v) : n(v.n), datos(new double[n])
    {
        for (unsigned i = 0; i < n; ++i)
            datos[i] = v.datos[i];
    }
    
    Vector(Vector&& v) : n(v.n), datos(v.datos)
    { v.datos = nullptr; }
    
    ~Vector() { delete[] datos; }
    
    Vector(initializer_list<double> const& list) noexcept
        : n(list.size()), datos(new double[n])
    {
        unsigned idx = 0;
        
        for (auto& i : list) {
            datos[idx] = i;
            ++idx;
        }
    }
    
    double& at(unsigned i)
    {
        if (i >= n)
            throw out_of_range("Fuera de rango");
            
        return datos[i];
    }
    
    double at(unsigned i) const
    {
        if (i >= n)
            throw out_of_range("Fuera de rango");
            
        return datos[i];
    }
    
    void print(ostream& os) const
    {
        os << '{';
        
        for (unsigned i = 0; i < n; ++i)
            os << datos[i] << ", ";
        
        os << '}';
    }
    
private:
    size_t n;
    double* datos;
};

ostream& operator<<(ostream& os, Vector const& v)
{
    v.print(os);
    
    return os;
}

int main()
{
    Vector v1(5, 1.2);
    Vector v2(4);
    
    // Vector v3; // Error
    // Vector v4 = 3; // Error
    
    Vector v5 = { 1, 2.5, 3 };
    
    cout << v1 << endl << v2 << endl << v5 << endl;
    
    Vector v6 = { 1, 2, 3, 4, 5, 6 };
    Vector v7(6);
    
    try {
        v7.at(0) = v6.at(9);
    } catch (out_of_range& e) {
        cout << e.what() << endl;
    }
    
    return 0;
}
