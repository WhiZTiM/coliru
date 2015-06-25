template <typename... Ts>
void foo(Ts..., int) {}

int main() {

    foo(42.f, 4);
}