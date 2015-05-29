    template <typename T, typename F>
    auto operator&=(F const& closure, T&& arg) {
        return closure(std::forward<T>(arg));
    }