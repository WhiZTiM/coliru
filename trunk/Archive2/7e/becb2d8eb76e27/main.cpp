#include <iostream>
#include <string>
#include <vector>


template<typename T>
     struct wrap
     {
      wrap() {
          std::cout << "def";
          }

      wrap(wrap&&) = default; // Defaulted marked as deleted - no ADL for you

      wrap(const wrap&) {
        std::cout << "copy";   
      }

     union {
        T t;
     };
     };

    struct S {
      S(){}
      S(const S&){} // Non trivial copy ctor
      S(S&&){}
    };

    typedef wrap<const S> W;

    W get() { return W(); } 



int main()
{
    W obj = get();
    std::cout << "hello";
    W obj2(std::move(obj));
}
