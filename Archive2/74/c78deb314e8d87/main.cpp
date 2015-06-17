#include <iostream>
#include <vector>
#include <cmath>

#include <memory>
class Containing {
    // class Nested;                 // [1]: This line seems required.
    class Nested {
        typedef std::shared_ptr<class Nested> Ptr;
        Ptr & ptr ();
        void foo (const Ptr &p) {
            p->ptr() = ptr()->ptr(); // [2]: Error here without [1]
        }
    };
};
int main () {}