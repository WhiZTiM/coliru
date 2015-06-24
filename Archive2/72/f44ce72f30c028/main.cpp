extern "C" int printf(const char *, ... );

auto inc = [](auto x) { return x + 1; };

auto zero = [](auto s) { return [](auto z) { return z; }; };

auto succ = [](auto n)
{
    return [=](auto s)
    {
        return [=](auto z) { return s(n(s)(z)); };
    };
};

auto pow = [](auto b) { return [=](auto e){ return e(b); }; };

template<unsigned N> auto n = succ(n<N-1>);
template<> auto n<0> = zero;

int main()
{
    printf("15**15 = %llu", pow(n<15>)(n<15>)(inc)(0ull));
}
