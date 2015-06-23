struct nonmovable {
    nonmovable() = default;
    nonmovable(nonmovable&&) = delete;
    nonmovable& operator=(nonmovable&&) = delete;
    nonmovable(const nonmovable&) = delete;
    nonmovable& operator=(const nonmovable&) = delete;
    
    template <typename...Args>
    nonmovable(Args&&...) {}
};


int main() {
    auto ptr = new nonmovable[2]{{42}, {13}};
    delete[] ptr;
}
