template <class T> struct C {
    void g();
};

class A { class B; class C; };

template <> struct C<A::B>;    // Ok
template <> void C<A::C>::g(); // Error 