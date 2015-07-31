#include <iostream>

class Af
{
public:

    Af () : i (0) {};
    virtual ~Af () {};
    
    virtual Af* Clone () const { Af* p_clone = new Af (); p_clone->operator= (*this); return p_clone; };
    
    virtual Af& operator= (const Af& i_other) { if (this == &i_other) { return *this; }; i = i_other.i; return *this; };
    
    int i;
};

class Bf : public Af
{
public:

    Bf () : j (0.0) {};
    
    virtual Af* Clone () const { Af* p_clone = new Bf (); p_clone->operator= (*this); return p_clone; };
    
    virtual Af& operator= (const Af& i_other) { if (this == &i_other) { return *this; }; Af::operator= (i_other); const Bf* p_in_other = dynamic_cast <const Bf*> (&i_other); if (0x0 == p_in_other) { return *this; }; j = p_in_other->j; return *this; };
    
    double j;
};

class A
{
private:

    Af* p_format;
    
public:

    A (Af& i_format) : p_format (i_format.Clone ()), format (*p_format) {};
    virtual ~A () { delete p_format; p_format = 0x0; }

    Af& format;
};

class B : public A
{
public:

    B (Bf& format) : A (format), format (dynamic_cast <Bf&> (A::format)) {};
    
    Bf& format;
};
    

int main()
{
    Bf format;
    format.i = 1;
    format.j = 1.2;
    
    B b (format);
    
    A& a = b;
    
    std::cout << "i: " << b.format.i << "\nj: " << b.format.j << "\n";
    std::cout << "i: " << a.format.i << "\n";
}
