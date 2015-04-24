// Terminal symbols:
struct Select {} select;
struct Where {} where;

// Nonterminal:
template<typename Left, typename Right> struct Pipeline {};

template<typename T, typename U>
auto operator|(T, U)
{
    return Pipeline<T, U>{};
}

// Utility for print type at compile time:
template<typename T> void type_is(T);

int main()
{
    // Create expression tree by parts, in different expressions:
    // 1:
    auto q1 = select | where;
    // 2:
    auto q2 = q1 | select;
    // Print type of q2:
    type_is(q2);
}
