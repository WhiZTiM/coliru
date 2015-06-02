#include <vector>

template <typename T>
class Base 
{
};

template <typename T>
class Derived : public Base<std::vector<T> > { 
};

template <typename T>
int bar(const std::vector< Base<T> >& y) {
}

int main() 
{
  std::vector< Base<double> > x;
  std::vector< Derived<double> > y;
  
  bar(x); // OK, can deduce the type, T = double
  bar(y); // boom
}