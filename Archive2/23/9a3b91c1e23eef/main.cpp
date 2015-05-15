struct Base{};
struct Derived: virtual Base{};

struct A: public Base{};

struct B: public A, public Base{};

struct C: public A, public Derived{}; // why no ambiguity here?

int main() {}