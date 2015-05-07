template<typename V>
struct pair {
    constexpr pair(const char *k, V &v)
        :k(k)
        ,v(v)
    {}

    const char *k;
    V &v;
};

template<typename V>
constexpr pair<V> json_pair(const char *k, V &v) {
    return pair<V>{k, v};
}

int i;

int main() {
    constexpr auto p0 = json_pair("i", i);
    
    (void)p0;
}