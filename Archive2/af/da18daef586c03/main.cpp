
struct G
{
    G(int) {}
};

struct Result
{
    Result() : g(1) {}
    G g;  
};

struct A
{
    A() {}
    
    Result m_tempStructResult;
};

int main()
{
    A{};
}
