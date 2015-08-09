struct A { protected: static const int x = 0; };

struct B : A { using A::x; };
struct C : A { };

struct D : B, C {};

int main() {
    D::x;
}