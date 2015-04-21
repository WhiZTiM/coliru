#include <iostream>
using std::cout;
using std::endl;

class FXX {
    public:
    FXX() {cout << "FXX default ctor" << endl;}
    //void channel() = 0;
    virtual void phrase() { cout << "Fearless" << endl;}
};
class Archer : public FXX {
    int shots_taken;
    public:
    Archer(int glengoole_blue) : shots_taken(glengoole_blue) {}
    virtual void phrase() { cout << "Phrasing BOOM!" << endl;}
};

class Lana : public Archer {
    public:
    Lana() {cout << "Lana default ctor" << endl;}
    virtual void phrase() = 0;
};
 
class AJ : public Lana {
    int diapers;
    public:
    AJ(int diapers_in) : diapers(diapers_in) {}
    virtual void phrase() {cout << "goo?" << endl;}
};

int main()
{
     AJ* aj = new AJ(5);
     aj->phrase();
}
