#include <memory>
#include <typeindex>
#include <typeinfo>
#include <iostream>

struct test {
    test() { std::cout << "constructed\n"; }
    ~test() { std::cout << "destructed\n"; }
};

struct fancy_type_erasure {
private:
    using ptr_type = std::unique_ptr<void, void(*)(void*)>;
    ptr_type ptr;
    std::type_index index;
public:
    fancy_type_erasure(): ptr{nullptr, [](void*){}}, index(typeid(nullptr)) {}
    template<typename T>
    fancy_type_erasure(T&& t): ptr{new T(std::move(t)), [](void* ptr) { delete static_cast<T*>(ptr); }}, index(typeid(T)) {}
    
    template<typename T, typename... Args>
    void emplace(Args&&... args) {
        ptr = ptr_type{new T(std::forward<Args>(args)...), [](void* ptr) { delete static_cast<T*>(ptr); }};
    }
    
    template<typename T>
    T* get() const noexcept {
        auto&& id = std::type_index(typeid(T));
        if(id == index) {
            return static_cast<T*>(ptr.get());
        }
        return nullptr;
    }
};

int main() {
    fancy_type_erasure any;
    any.emplace<test>();
}