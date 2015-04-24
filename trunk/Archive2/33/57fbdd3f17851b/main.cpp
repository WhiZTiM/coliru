template<unsigned N>
constexpr bool test(const char (&s)[N])
{
    for(auto x : s)
        if(x == 'x') return false;
    return true;
}

int main()
{
    static_assert(test("abc"));
    static_assert(test("zyx"));
}
