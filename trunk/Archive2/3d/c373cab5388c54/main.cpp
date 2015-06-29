// In X.hpp

#include <vector>

struct Y;

struct X
{
    // ...
    X(X const&);
    // ...
private:
    std::vector<Y> v;
};

// In X.cpp

// ...
X(X const&) = default;
// ...

// In main.cpp

int main()
{
    // Use X without seeing the definition of Y
}