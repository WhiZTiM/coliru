#include <unordered_set>

struct X
{
    std::string name;

    struct hash
    {
        auto operator()( const X& x ) const
        { return std::hash< std::string >()( x.name ); }
    };
};

int main()
{
    std::unordered_set< X, X::hash > x;
}
