auto recursive = [](auto f)
{
    return [=](auto... xs)
    {
        return f(f, xs...);
    };
};

auto test()
{
    auto factorial = recursive([](auto &self, auto x) -> decltype(x)
    {
        return x ? self(self, x-1)*x : 1;
    });

    return factorial(5);
}
