#include <iostream>

using namespace std;

class V
{
public:
    void f(){ cout<<"f() de V"<<endl;}
    virtual void g() = 0;
    virtual void g(int i){cout<<"g(" << i << ") de V"<<endl;}
    void h(){ cout<<"h() de V"<<endl;}

protected:
    int v_;
};

class W: virtual public V
{
public:
    void f(int i){cout << "f(" << i << ") de W" << endl;}
    void g(){ cout << "g() de W" << endl;}
    
protected:
    int w_;
};

class X: virtual public V
{
public:
    void f(){cout << "f() de V" << endl;}
    void h(){ cout << "g() de V" << endl;}

protected:
    int x_;
};

class Z: public W, public X
{
    int z_;
};

class Y: public W
{
public:
    void h(){cout << "h() de Y" << endl;}
    void g(){ cout << "g() de Y" << endl;}

protected:
    int y_;
};

void f(V& v)
{
    cout << "f() externa" << endl;
    v.f();
    v.g();
    v.h();
    cout << "----------------------" << endl;
}

int main()
{
     cout <<"=========================="<<endl;
     
    V *pb; //B no puede construir objetos ya que es abstracta
    W w;
    //X x;; //Tb es abstracta
    Y y;
    Z z;
    
    f(w); f(y); f(z);

     cout <<"=========================="<<endl;

    z.X::f();
    //z.f(); //Ambigüedad ya que las tres f() son funciones distintas, no corresponde a una sobrecarga ya que f no es virtual.
    //z.f(5);
    //z.f(3,7);
    z.g();
    z.h();

    cout <<"=========================="<<endl;

    pb=new Z;
    pb->f(); //Puse que daba ambigüedad por la cara...
    //pb->D2::f(); //pb no dispone de la f de D2 ya que D2 no es un subobjeto de B, sino que B es un subobjeto de D2
    pb->g();
    pb->h();
    delete pb;
}
