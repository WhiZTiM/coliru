class A {
    template <int=0> void f();
};
template <int=1>
void A::f(){}

int main () {}