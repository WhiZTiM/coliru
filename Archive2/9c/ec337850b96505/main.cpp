#include <iostream>
#include <memory>
#include <utility>

class any_list {
public:
    template<typename L>
    explicit any_list(L list) : list(new derived<L>(std::move(list))) { }

    any_list(any_list&&) = default;
    any_list& operator=(any_list&&) = default;

    virtual ~any_list() = default;

    virtual void print(std::ostream& stream) const {
        list->print(stream);
    }

private:
    class base {
    public:
        virtual ~base() = default;

        virtual void print(std::ostream& stream) const = 0;
    };

    template<typename L>
    class derived : public base {
    public:
        explicit derived(L list) : list(std::move(list)) { }

        virtual void print(std::ostream& stream) const override {
            stream << list;
        }

    private:
        L list;
    };

    std::unique_ptr<base> list;
};

std::ostream& operator<<(std::ostream& stream, any_list const& list) {
    list.print(stream);
    return stream;
}

template<typename T>
struct list {
    list(T head, std::unique_ptr<list> tail)
        : head(std::move(head))
        , tail(std::move(tail)) { }

    T head;
    std::unique_ptr<list> tail;
};

template<typename T>
std::ostream& operator<<(std::ostream& stream, list<T> const* list) {
    stream << "(cons";
    stream << " " << list->head;
    if (list->tail != nullptr) {
        stream << " " << &*list->tail;
    }
    stream << ")";
    return stream;
}

int main() {
    list<any_list> xs(any_list(&xs), nullptr);
    std::cout << &xs << '\n';
};