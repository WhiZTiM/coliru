using namespace std;
#include <iostream>
#include <string>

template<class T> class C
{
public:
    T x;
    static bool flag;
private:
    T z;
public:
    C():C(1) {C<T>::msg("Class C default object created!");};
    C(const T& x):x(x),z(x) {C<T>::msg("Class C initialized object created!");};
    C(const C& c) {this->x=c.x;this->z=c.z;C<T>::msg("Class C copied object created!");};
    virtual ~C() {C<T>::msg("Class C object destroyed!");};
    C* operator&() const {return this;};
    C& operator=(const C& c) {this->x=c.x;this->z=c.z;return *this;};
    bool operator==(const C c) const {return (this->x==c.x && this->z==c.z);};
    void operator++() {++(this->z);};
    C& operator++(int) {(this->z)++;return *this;};
    void operator--() {--(this->z);}
    C& operator--(int) {(this->z)--;return *this;};
    static void msg(const string str) {if(C<T>::flag){cout<<str<<endl;}};
    virtual void foo(T& x) const {x=this->z;};
}
;

template<class T> class Cxx:public C<T>
{
private:
    T z;
public:
    Cxx() {C<T>::msg("Class Cxx object created!");};
    ~Cxx() {C<T>::msg("Class Cxx object destroyed!");};
    T foo() {return this->z;};
}
;

template<class T> bool C<T>::flag=false;

int main()
{
    int x=7;
    C<int>::flag=true;
    C<int> *p1=new C<int>(x);
    C<int> *p2=new C<int>(*p1);
//    Cxx<int> *pxx=new Cxx<int>();
//    cout<<p1->x<<endl;
//    cout<<x<<endl;
    p1->foo(x);
    cout<<x<<endl;
    (*p2)--;
    p2->foo(x);
    cout<<x<<endl;
//    delete pxx;
    delete p1;
    delete p2;
    return static_cast<int>(NULL);
}
