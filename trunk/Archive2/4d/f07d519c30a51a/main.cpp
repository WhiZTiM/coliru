#include <iostream>

using namespace std;


class Three;

class One
{
public:
    One(){};
    virtual Three& doIt() = 0;
    operator Three();
};

class Two: public One
{
public:
    Two(){};
    virtual Three& doIt();
    Two& operator=(const One& one) {
        // I do nothing, I'm here just so you will get compiled
        return *this;
    }
};

class Three: public Two
{
public:
    Three(const Two& two) : Two(two){};
    Two& operator*() { return *this; }
};

One::operator Three() {
    // I do nothing, I'm here just so you will get compiled
    return Three(Two());
}

Three& Two::doIt() { 
    static Three three(*this);
    return three;
}


int main() {
    One* pOne = new Two();
    Three& three = pOne->doIt();
    *three = *pOne;
    three = *pOne;
    cout << "hip hip hurray";
    return 1;
}
