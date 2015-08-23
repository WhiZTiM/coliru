#include <vector>
#include <iostream>

template < typename T > class TD; // type visualiser

template<class T>
class A
{
    public:
    A(T arg) { _data = arg; }
    
    template<typename D>
    operator A<D>() {
      static_assert(std::is_same<D, float>::value || std::is_same<D, double>::value, "double/floats allowed only");
      //TD<D>();  // D is float here
      return static_cast<D>(_data);
    }

    T _data;
};

typedef A<float> A_f;
typedef A<double> A_d;
typedef A<int> A_i;

int main() {
   A_f f(3.14151);
    A_d d(3.14152);
    
    std::cout << f._data << std::endl;
    std::cout << d._data << std::endl;    
    
    f = (A_f)d;
    //f = (A_i)d; // static assertion here
    
    std::cout << f._data << std::endl;
    return 0;
}