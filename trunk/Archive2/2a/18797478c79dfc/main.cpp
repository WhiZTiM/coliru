#include "hello.hpp"

#include <iostream>

template<> void hello<void>()
{ std::cout << "hello\n"; }