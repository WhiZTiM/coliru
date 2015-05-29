namespace ns
{
struct foo
{
    static constexpr auto bar = 42;
};
}

constexpr int ns::foo::bar;

int main()
{}
