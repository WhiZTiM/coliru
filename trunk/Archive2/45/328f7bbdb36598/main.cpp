#include <iostream>

template <typename A, typename... Bs>
struct Hello;

template <typename A>
struct Hello<A> {
  template <typename A2>
  friend std::ostream & operator<<(std::ostream & s, const Hello<A2> & h);
};

template <typename A, typename... Bs>
struct Hello {
  template <typename A2, typename... B2s>
  friend std::ostream & operator<<(std::ostream & s, const Hello<A2,B2s...> & h);
};


template <typename A2>
std::ostream & operator<<(std::ostream & s, const Hello<A2> & h) {
  return s << "specialized\n";
}

template <typename A2, typename... B2s>
std::ostream & operator<<(std::ostream & s, const Hello<A2,B2s...> & h) {
  return s << "generic\n";
}


int main()
{
  std::cout << Hello<int>() 
            << Hello<float>() 
            << Hello<int,int>() 
            << Hello<int,float>();
}
