struct X
{
    template<class U>
    X(U) {}
};

struct Y : X { using X::X; };

int main()
{
    struct Z : X { using X::X; };
    Y y(42); // fine
    Z z(42); // ICE
}