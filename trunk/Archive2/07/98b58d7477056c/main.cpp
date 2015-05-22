template<typename F, typename Result, typename ...Params>
Result concrete_wrapper(const void *f, Params... params)
{
    return (*static_cast<const F*>(f))(params...);
}

template<typename Signature>
class function_non_owning;

template<typename Result, typename ...Params>
class function_non_owning<Result(Params...)>
{
    const void *f = nullptr;
    Result (*wrapper)(const void *, Params...) = nullptr;
public:
    function_non_owning() = default;

    template<typename F>
    function_non_owning(const F &f)
        : f(&f), wrapper(&concrete_wrapper<F, Result, Params...>)
    {}

    Result operator()(Params... params) const
    {
        return wrapper(f, params...);
    }
};

void baz()
{
    function_non_owning<unsigned(unsigned)> f = [&](unsigned n)
    {
        return n ? f(n - 1) : 1;
    };
    volatile auto x = f(5);
    (void)x;
}
