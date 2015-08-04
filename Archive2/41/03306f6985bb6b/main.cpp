
template<class T, class F>
void func(F T::*const) {}

struct Foo { int i; };

int main() {
    func(&Foo::i);
}
