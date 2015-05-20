template<typename...> struct foo;

template<typename Only>
struct foo<Only> {};

template<typename First, typename... Rest>
struct foo<First, Rest...>: foo<Rest...> {};

template<typename Only>
void bar(Only) {}

// instead, if nullary calls should be allowed:
// void bar() {}

template<typename First, typename... Rest>
void bar(First, Rest... rest)
{
    bar(rest...);
}

int main()
{
    foo<int, void, long, char> {};
    bar(0, 'a', "hello", nullptr);
}
