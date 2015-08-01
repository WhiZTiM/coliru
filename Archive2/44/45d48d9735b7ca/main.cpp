struct S {constexpr operator int(){return{};}};
constexpr S f() {S s;return s;}

template<int>
void h() {}

int main() {
    h<f()>();
}