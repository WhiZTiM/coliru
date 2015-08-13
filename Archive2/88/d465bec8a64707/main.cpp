#include <iostream>
#include <type_traits>

// Managers
// ---------------------------------------------------------------
struct TotoManager { void print() { std::cout << "TOTO!\n"; } };
struct TitiManager { void print() { std::cout << "TITI!\n"; } };

// Behavior
// ---------------------------------------------------------------
#define FORWARD_STATE_GETTER( _func_ ) \
    template<typename O = State, typename R = decltype(((O*)nullptr)->_func_())> \
    R _func_() { return state->_func_(); }
    
template<typename State>
struct GameBehavior
{
    State* state;

    FORWARD_STATE_GETTER( getToto )
    FORWARD_STATE_GETTER( getTiti )
};

// States
// ---------------------------------------------------------------
struct State1
{
    TotoManager t;

    TotoManager& getToto() { return t; }
};

struct State2
{
    TitiManager t;

    TitiManager& getTiti() { return t; }
};

// Test
// ---------------------------------------------------------------
int main()
{
    State1 s1;
    State2 s2;

    GameBehavior<State1> g1 = { &s1 };
    GameBehavior<State2> g2 = { &s2 };

    g1.getToto().print();   // OK
    //g2.getToto().print(); // error: no matching member function for call to 'getToto'
    //g1.getTiti().print();   // error: no matching member function for call to 'getTiti'
    g2.getTiti().print(); // OK
}
