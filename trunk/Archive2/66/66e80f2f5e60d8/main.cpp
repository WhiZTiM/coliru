union test {
    int x;
    float y;
};

struct other {
    test storage;
    other() {
        storage.x = 20;
    }
    
    const int& get() const noexcept {
        return storage.x;
    }
};

int main() {
    other okay;
    return okay.get();
}
    