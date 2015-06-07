struct X
{
    template<class = int>
    X() {}
};

struct Y : X { using X::X; };

int main()
{
}