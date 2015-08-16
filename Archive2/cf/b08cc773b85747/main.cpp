#include <iostream>
#include <memory>
#include <vector>

struct base {
    virtual
    ~base() { }
    
    virtual void
    f() = 0;
};

struct foo : base {
    void
    f() override {
        std::cout << "foo\n";
    }
};

struct bar : base {
    void
    f() override {
        std::cout << "bar\n";
    }
};

struct states {
    std::vector<std::unique_ptr<base>> stack;
    
    template <typename T>
    void
    add() {
        stack.push_back(std::make_unique<T>());
    }
    
    void
    call_all() {
        for (auto& state: stack)
            state->f();
    }
};

int
main() {
    states s;
    s.add<foo>();
    s.add<bar>();
    s.call_all();
}
