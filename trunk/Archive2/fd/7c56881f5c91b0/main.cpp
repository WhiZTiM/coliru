#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
class A {
private:
    double x;
    long y;
public:

    A(long xx, double yy) :x(xx), y(yy){};
    ~A();
    void Display();
    friend std::ostream &operator <<(std::ostream&, const A*);
};

std::ostream &operator <<(std::ostream &os, const A* a) {
    os << a->x << ' ' << a->y;   
    return os;
}

template<typename T>
std::ostream &operator <<(std::ostream &os, const std::vector<T> &v) {
    using namespace std;
    copy(v.begin(), v.end(), ostream_iterator<T>(os, "\n"));
    return os;
}

void FillA(std::vector<A*>& v) {
    v.push_back(new A{1,2});
    v.push_back(new A{2,3});
}

int main()
{
    std::vector<A*> aVect;
    FillA(aVect);
    std::cout << aVect;

    return 0;
}