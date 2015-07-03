#include <iostream>
#include <typeinfo>
#include <string>
#include <cstdlib>
#include <cxxabi.h>

template <typename T>
std::string print_type ()
{
  int status;
  std::string tname = typeid(T).name();
  char *demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &status);
  if(status == 0) {
    tname = demangled_name;
    std::free(demangled_name);
  }
  return tname;
}

#include <boost/variant.hpp>

void* ptr = nullptr;

struct A { A () { } ~A () { ptr = this; } };
struct B { B () { } B (B const&) { if (ptr == this) throw 1; } };
struct C { };

using namespace boost;

struct print_types: static_visitor<>
{
    template <typename T> void operator() (T const&) const
	{ std::cout << "Variant contains `" << print_type<T> () << "'\n"; }
};

int main ()
{
    // init variant with A
	variant<A, B, C> var { A {} };
	apply_visitor (print_types {}, var);

	// copy B into variant
    try { var = B {}; } catch (...) { }

    // what type is inside variant now?
	apply_visitor (print_types {}, var);
}
