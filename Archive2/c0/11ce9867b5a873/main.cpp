struct X
{
    template<class = int>
    X() {}
};

struct Y : X
{
    using X::X; // error C2535: 'Y::Y(void)': member function already defined or declared
};

int main()
{
}