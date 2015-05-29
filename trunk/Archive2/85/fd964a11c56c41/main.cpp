#include "hello.hpp"

#include <iostream>

template<typename> void hello()
{ std::cout << "hello\n"; }

template void hello<void>();