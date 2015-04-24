#include <type_traits>

struct component {};

namespace detail {
template<typename T>
constexpr bool is_component() noexcept {
    static_assert(std::is_base_of<component, T>::value, "Type must be a component");
    return true;
}

template<typename... Args>
constexpr bool are_components() {
    using swallow = bool[];
    return (void(swallow{ (is_component<Args>(), true)... }), true);
}
} // detail

#include <typeindex>
#include <typeinfo>
#include <memory>
#include <vector>

struct entity {
private:
    using component_ptr = std::unique_ptr<component, void(*)(component*)>;
    struct entry {
        std::type_index index;
        component_ptr ptr;
        entry(std::type_index id): index(id), ptr(nullptr, [](component*) {}) {} // this entry is typically for searching only
        entry(std::type_index id, component_ptr comp): index(id), ptr(std::move(comp)) {}
    };
    std::vector<entry> components;

    auto find(const entry& entry) const -> decltype(components.begin()) {
        auto first = components.begin();
        auto last  = components.end();
        decltype(first) it;
        auto count = last - first;
        while(count > 0) {
            it = first;
            auto step = count / 2;
            it += step;
            if(entry.index < it->index) {
                first = ++it;
                count -= step + 1;
            }
            else {
                count = step;
            }
        }
        return first;
    }

    template<typename T>
    bool has_impl() const {
        detail::is_component<T>();
        return find(std::type_index(typeid(T))) != components.end();
    }

    template<typename T, typename... Args>
    typename std::enable_if<(sizeof...(Args) >= 1), bool>::type has_impl() const {
        return has_impl<T>() && has_impl<Args...>();
    }

    template<typename T>
    void remove_impl() {
        detail::is_component<T>();
        auto it = find(std::type_index(typeid(T)));
        if(it != components.end()) {
            components.erase(it);
        }
    }

    template<typename T, typename... Args>
    typename std::enable_if<(sizeof...(Args) >= 1)>::type remove_impl() {
        remove_impl<T>();
        remove_impl<Args...>();
    }
public:
    entity() = default;

    template<typename T>
    T* get() const {
        detail::is_component<T>();
        auto it = find(std::type_index(typeid(T)));

        if(it == components.end()) {
            return nullptr;
        }

        return static_cast<T*>(it->ptr.get());
    }

    template<typename T, typename... Args>
    void emplace(Args&&... args) {
        detail::is_component<T>();
        component_ptr c{ new T(std::forward<Args>(args)...), [](component* ptr) { delete static_cast<T*>(ptr); } };
        auto&& id = std::type_index(typeid(T));
        auto&& it = find(id);
        components.emplace(it, id, std::move(c));
    }

    template<typename... Args>
    bool has() const {
        return has_impl<Args...>();
    }

    template<typename... Args>
    void remove() {
        return remove_impl<Args...>();
    }
};

#include <iostream>

struct health_component : component {
    int hp = 100;
};

struct position_component : component {
    int x = 30;
    int y = 40;
};

int main() {
    entity lol;
    lol.emplace<health_component>();
    lol.emplace<position_component>();
    {
        auto health = lol.get<health_component>();
        if(health) {
            std::cout << "Subtracting HP\n";
            health->hp -= 20;
            std::cout << "HP: " << health->hp << '\n';
        }
    }
}