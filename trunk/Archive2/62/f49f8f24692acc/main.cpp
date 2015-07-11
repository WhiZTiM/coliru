template <typename T>
void f() { }

using F = void(*)();

F fint = f<int>;

int main() {
    fint();
}