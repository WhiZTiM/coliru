#include <iostream>
using std::cout;
using std::endl;

class FXX {
    public:
    FXX() {cout << "FXX default ctor" << endl;}
    void channel();
    virtual void phrase() { cout << "Fearless" << endl;}
};
class Archer : public FXX {
    int shots_taken;
    public:
    Archer(int glengoole_blue) : shots_taken(glengoole_blue) {}
    virtual void phrase() { cout << "Phrasing BOOM!" << endl;}
};

int main()
{
    Archer* sterling = new Archer(10);
    sterling->phrase();
}
