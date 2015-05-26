#include <utility>     // std::move

struct Myclass 
{
   Myclass &  truc() &  { return           *this;  }
   Myclass && toto() && { return std::move(*this); }
};

void foo(Myclass &) {}

Myclass bar() { return Myclass(); }

int main()              
{
  foo( bar().truc() );   // error
//foo( bar().toto() );   // error
}
