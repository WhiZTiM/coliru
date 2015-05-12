#include <iostream>

template <typename A, typename... Bs>
struct Hello {
  friend std::ostream & operator<<(std::ostream & s, const Hello<A,Bs...> & h) {
    return s << "generic\n";
  }
};

template <typename A>
struct Hello<A> {
  friend std::ostream & operator<<(std::ostream & s, const Hello<A> & h) {
    return s << "specialized\n";
  }
};

int main()
{
  std::cout << Hello<int>() << Hello<float>() << Hello<int,int>() << Hello<int,float>();
}
