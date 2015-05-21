
struct Functor {
    template<typename F>
    void operator()(int n, F const & f) const { if (n) f(n-1, f); }
};

int main() {
    Functor f;
    f(5, f);
    
    //auto const lambda = [](int n, auto const & f){ if (n) f(n-1, f); };
    //lambda(5, lambda);
}
