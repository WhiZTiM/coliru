#include "implementation.hpp"

#include <cstdlib>

int
main()
{
    visitor{}(V{B{}});
    return EXIT_SUCCESS;
}