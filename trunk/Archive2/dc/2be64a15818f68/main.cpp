#include<iostream>

struct Outer {
    class Inner {
       friend class TheFriend; // ill-formed NDR because meaning is changed by subsequent declaration.
       static int const i = 0;
    };
    struct TheFriend {
        static int const j = Inner::i;
    };
};

struct TheFriend {
    static int const k = Outer::Inner::i;
};

/*int main()
{
    TheFriend global;
    global.f();
}*/