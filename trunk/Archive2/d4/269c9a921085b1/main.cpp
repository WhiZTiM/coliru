
struct G
{
    G(int) {}
};

struct Result
{
    int x;
    G g;  
};

struct A
{
    A() : m_tempStructResult{1, G(1)} {}
    
    Result m_tempStructResult;
};

int main()
{
    A{};
}
