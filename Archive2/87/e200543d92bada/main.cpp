#include <iostream>
using namespace std;

class Pokemon {};

class Zubat : protected Pokemon {
  public:
  virtual void barf() {}
};

#define DIV(X) X *X^X\ */~X
#define OP(O) O
#define ABS(X) ABS2(X , X OP(X) X)
#define ABS2(_, X) X OP(X) X
#define STR(...) ABS(__VA_ARGS__)
#define M(i, _) STR(),i,_
template<typename... P> auto pokeballAt() {
    try {
     throw M( ( ((bool)nullptr ? 0x0 : ( [](){} ) ) , ... , P()) , ~31);
    } catch (...) {
        cout << "gotta catch 'em all";
    }
}

int main()
{
    
    pokeballAt<Zubat>();
    
    
    return 0; 
}