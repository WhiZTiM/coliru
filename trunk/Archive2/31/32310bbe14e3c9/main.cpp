// Utility for print type at compile time:
template<typename T> void type_is(T);

// Terminal symbols:
struct Select {} select;
struct Where {} where;

// Nonterminal:
template<typename Left, typename Right>
struct Pipeline {};

// Process expression tree:
template<typename _>
struct CheckGrammar
{
    using type = bool;
};

template<typename Left, typename Right>
struct CheckGrammar<Pipeline<Left, Right>>
{
    using type = typename CheckGrammar<Left>::type; // Recurse to left sub-tree
};

template<typename _>
struct CheckGrammar
<
    Pipeline<Pipeline<Pipeline<_, Where>, Select>, Where> // Pattern matching
>
{
    using type = typename _::error_in_grammar_after;
};

template<typename T, typename U>
auto operator|(T, U)
{
    auto result = Pipeline<T, U>{};
    using run = typename CheckGrammar<decltype(result)>::type; // Run grammar check at compile-time
    return result;
}

int main()
{
    auto q1 = where | select | select; // OK
    auto q2 = q1 | where; // OK
    auto q3 = q2 | select | where; // ERROR
}
