namespace blah
{
namespace blub
{
template<class> struct X{};
}

using ::blah::blub::X;

}

namespace blah
{
template<> struct X<int>{};
}

int main() {
}