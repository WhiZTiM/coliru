#include <memory>

struct X
{
    X(int){}
    X() = delete;
    X(X const&) = delete;
    X(X&&) = delete;
};

int main()
{
    static int const N = 3;
    std::unique_ptr<X[]> p((X*)malloc(N * sizeof(X)));
    new (&p[0]) X(0);
    new (&p[1]) X(1);
    new (&p[2]) X(2);
}