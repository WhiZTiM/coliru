#include <vector>

enum class A::B;

class A : public std::vector<A::B>
{
public:
    enum class B
    {
    };
};

int main()
{
}