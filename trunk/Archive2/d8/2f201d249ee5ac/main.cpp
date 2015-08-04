#include <iostream>
#include <vector>
#include <string>
#include <utility>

int  main()
{
    {
        // copied
        std::string st = "hello";
        std::vector<std::string> vec;
        vec.push_back(st); // copy, not move; st is still intact
        std::cout << "'" << st << "'\n" ; // prints "hello"

        int i = 78 ;
        int j = i ; // copy
        std::cout << i << ' ' << j << '\n' ; // prints 78 78
    }

    {
        // moved
        std::string st = "hello";
        std::vector<std::string> vec;
        vec.push_back( std::move(st) ) ; // copy, not move; st is still intact

        // std::string is a type defined by the standard library; for such types:
        // "Unless otherwise specified, such moved-from objects shall be
        // placed in a *valid* but *unspecified* state." - IS

        // all that the standard requires is that this would not fail.
        std::cout << "'" << st << "'\n" ; //  typically, prints the empty string "" (does nothing)

        // note: for a user-defined type, the only requirement is that a moved-from object
        // is safely destructible. ie, its destructor will not engender undefined behaviour

        int i = 78 ;
        int j = std::move(i) ; // move; however int has a trivial move constructor
                               // ie. its move does the same thing as its trivial copy constructor
                               // ie. the int is copied/moved "as-if" by std::memmove()
                               // the original is value is still there after the move
        std::cout << i << ' ' << j << '\n' ; // prints 78 78
    }
}
