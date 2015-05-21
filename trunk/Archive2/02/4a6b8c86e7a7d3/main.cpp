int main() {
    auto const lambda = [&](int n, auto const & f){ if (n) f(n-1, f); };
    lambda(5, lambda);
}
