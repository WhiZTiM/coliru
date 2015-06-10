
struct G
{
    G(int) {}
};

struct A
{
    A() {}
    
    G g = G(1);
};

int main()
{
    A{};
}
