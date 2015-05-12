struct fn
{
    template <typename ... Args>
        static constexpr bool call (Args ... ) { return true; }
};

template <typename ... T>
struct f {
    static constexpr bool v = false;
};

template <typename ... Ts, bool F = fn::call(f<Ts>::v ...)>
    void hoge () {}

int main () {}