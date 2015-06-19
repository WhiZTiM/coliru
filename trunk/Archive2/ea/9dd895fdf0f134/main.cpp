struct A
{
    A(int) {} // converting constructor
    A(int, int) {} // converting constructor (C++11)
    operator int() const { return 0; }
};
 
struct B
{
    explicit B(int) {}
    explicit B(int, int) {}
    explicit operator int() const { return 0; }
};
 
int main()
{
    A a1 = 1; // OK: copy-initialization selects A::A(int)
    A a2(2); // OK: direct-initialization selects A::A(int)
    A a3 {4,5}; // OK: direct-list-initialization selects A::A(int, int)
}