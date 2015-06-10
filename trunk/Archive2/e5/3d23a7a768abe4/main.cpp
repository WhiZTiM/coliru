
struct G
{
    G(int) {}
};

struct Result
{
    G g = G(1);  
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
