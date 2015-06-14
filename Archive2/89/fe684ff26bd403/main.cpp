#include<iostream>
#include<ostream>


template<class T1, class T2>
class par
{
public:
    par(const T1& x=T1(), const T2& y=T2())
        :prim(x), segund(y)
    {}

    T1 primero() const {return prim;}
    T1& primero() {return prim;}
    T2 segundo() const {return segund;}
    T2& segundo() {return segund;}

protected:
    T1 prim;
    T2 segund;
};

template<class T1, class T2>
ostream& operator<<(ostream& os, const par<T1,T2>& op)
{
    return os << op.primero() << ", " << op.segundo();
}

//Utilizo una clase en vez de un using ya que sino estaría creando
// un alias que podría dar lugar a confusión en alguna sobrecarga
class racional: public par<int,unsigned>
{
public:
    using par<int,unsigned>::par;
};

racional operator++(racional const& op1, racional const& op2)
{
    int numerador= op1.primero()*op2.segundo()+op2.primero()*op1.segundo();
    unsigned denominador= op2.segundo()*op1.segundo();
    return racional(numerador,denominador);
}

class complejo: public par<double,double>
{
public:
    using par<double,double>::par;

    complejo operator+=(complejo cons& op)
    {
        primero()= primero()+op.primero();
        segundo()+=op.segundo());

        return *this;
    }
};

int main()
{
    int a=1,b=2,c=3;
    double d=3.5,e=4.8;
    par<int,int>(a,b) ab;
}