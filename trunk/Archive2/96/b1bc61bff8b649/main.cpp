#define A S()

struct b {};

struct S : b {
    A: ::b() {}    
};