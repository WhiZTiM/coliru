#include <iostream>
#include <string>
#include <functional>

using std::cout;
using std::endl;
using std::string;

class FOO
{
public:
  void operator() (string word)         // first: functor
  {
    cout << word << endl;
  }

  void m_function(string word)          // second: member-function
  {
    cout << word << endl;
  }
} FUNCTOR;


void function(string word)              // third: non-member function
{
  cout << word << endl;
}

template<class T>
void eval(T fun)
{
  fun("Using an external function");
}

int main()
{
    FUNCTOR("Normal call");
    eval(FUNCTOR);

    function("Normal call");
    eval(function);

    FUNCTOR.m_function("Normal call");
    eval(std::bind(&FOO::m_function, FUNCTOR, std::placeholders::_1));
    eval([&]( char const *c ) { FUNCTOR.m_function(c); });
}
