constexpr int foo();
char str[foo()];
constexpr int foo() { return sizeof(str); }

int main() {}