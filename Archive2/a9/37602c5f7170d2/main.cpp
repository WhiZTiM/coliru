#include <iostream>
#include <memory>
#include <utility>

struct printable {
    virtual ~printable() = default;

    virtual void print(std::ostream& stream) const = 0;
};

std::ostream& operator<<(std::ostream& stream, printable const* p) {
    p->print(stream);
    return stream;
}

template<typename T>
struct list : printable {
    list(T head, std::unique_ptr<list> tail)
        : head(std::move(head))
        , tail(std::move(tail)) { }

    void print(std::ostream& stream) const override {
        stream << "(cons";
        stream << " " << head;
        if (tail != nullptr) {
            stream << " " << &*tail;
        }
        stream << ")";
    }

    T head;
    std::unique_ptr<list> tail;
};

int main() {
    list<printable*> xs(&xs, nullptr);
    std::cout << &xs << '\n';
};