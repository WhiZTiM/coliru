struct Select {} select;
struct Where {} where;

template<typename Left, typename Right>
struct Pipeline {};

template<typename T, typename U>
auto operator|(T, U)
{
    return Pipeline<T, U>{};
}

template<typename T> void type_is(T);

int main()
{
    auto q1 = select | where;
    auto q2 = q1 | select;
    type_is(q2);
}
