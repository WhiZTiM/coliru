#include <iostream>
#include <array>

struct testy;

class proxy
{
private:
    testy& _t;
    int _idx;
public:
    proxy(testy& t, int idx): _t(t), _idx(idx) {}
    proxy& operator=(double val);
    operator double() const; // conversion to double

};

struct testy {
    std::array<double, 10> data;
    double operator[] (int idx) const { return 1 / data[idx]; }
    proxy operator[](int idx)        {return proxy(*this, idx);}
};

proxy& proxy::operator=(double val)
{
    _t.data[_idx] = 1. / val;
    return *this;
}

proxy::operator double() const
{
    return _t.data[_idx];
}

int main()
{
    testy Pineapple;
    Pineapple[1] = 0.1;
    std::cout << Pineapple[1] << std::endl;
}