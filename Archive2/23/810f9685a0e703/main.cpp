#include <iostream>



/*
 * This simple definition is the only one that is available
 * to external units.
 * The file is named "blabla_exported.h"
 */

template <typename T>
struct Blob {
    template <typename X>
    int blib(X x);
};

/*
 * The actual implementation of the function template is in another file
 * This file is not available to external units
 */
 
 template <typename T>
 template <typename X>
 int Blob<T>::blib(X x) {
     /* The actual template uses a third party lib
      * whose headers are not available to the "external units" ...
      */
     return 42;
 }

/* My need:
 * Get the function template specializations I need
 * to be compiled
 */

int main() {
    Blob<int> t;
    std::cout << t.blib(2.0) << std::endl;
    return 0;
}