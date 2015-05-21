struct Fuctor {
    template <typename F>
    void operator()(int n, F const& f) const {
        if(n){ f(n-1, f); }
    }
};

int main() {
    Fuctor f;
    f(5, f);
}
