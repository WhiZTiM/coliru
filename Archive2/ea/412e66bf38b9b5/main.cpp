template <typename X>
struct BaseT
{
    void foo() { }
};

struct Derive : public BaseT<42>
{
    void bar() { foo(); }
};

int main()
{
}
