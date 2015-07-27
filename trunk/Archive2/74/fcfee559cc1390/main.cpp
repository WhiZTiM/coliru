namespace MyClass {
    static const char CHAR_S = '<';
} // namespace MyClass

int main() {
    using namespace MyClass;
    char separator = CHAR_S;
    return 0;
}