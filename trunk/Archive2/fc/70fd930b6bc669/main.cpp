#include <string>
#include <iostream>
#include <sstream>
 
template <typename t>
constexpr t pow(t base, int exp) {
  return (exp > 0) ? base * pow(base, exp-1) : 1;
}

template <char...> struct literal;
template <> struct literal<> {
  static const unsigned int to_int = 0;
};
template <char c, char ...cv> struct literal<c, cv...> {
  static const unsigned int to_int = (c - '0') * pow(10, sizeof...(cv)) + literal<cv...>::to_int;
};

template <int N> struct factorial {
  static const unsigned int value = N * factorial<N - 1>::value;
};
template <> struct factorial<0> {
  static const unsigned int value = 1;
};

template <char ...cv>
constexpr unsigned int operator "" _fac()
{
  return factorial<literal<cv...>::to_int>::value;
}

template <char ... cv>
struct tag
{
    
};

template <char ...cv>
constexpr tag<cv...> operator "" _tagged()
{
  return tag<cv...>();
}

int main()
{
    auto lll = 3_fac;
    auto ttt = "123"_tagged;
    std::cerr << lll << std::endl;
    std::cerr << ttt << std::endl;
    
    // greet the user
    std::string name;
    std::cout << "What is your name? ";
    std::getline(std::cin, name);
    std::cout << "Hello " << name << ", nice to meet you.\n";
 
    // read file line by line
    std::istringstream input;
    input.str("1\n2\n3\n4\n5\n6\n7\n");
    int sum = 0;
    for (std::string line; std::getline(input, line); ) {
        sum += std::stoi(line);
    }
    std::cout << "\nThe sum is: " << sum << "\n";
}