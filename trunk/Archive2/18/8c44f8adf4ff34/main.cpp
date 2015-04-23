#include <type_traits>

namespace fire {
struct Component {
    virtual ~Component() = default;
};

namespace detail {
template<typename T>
constexpr bool is_component() noexcept {
    static_assert(std::is_base_of<Component, T>::value, "Type must be a component");
    return true;
}

template<typename... Args>
constexpr bool are_components() {
    using swallow = bool[];
    return (void(swallow{ (is_component<Args>(), true)... }), true);
}
} // detail
} // fire

#include <typeindex>
#include <typeinfo>
#include <memory>
#include <vector>

namespace fire {
struct Entity {
private:
    struct Entry {
        std::type_index index;
        std::unique_ptr<Component> component;
        Entry() = default;
        Entry(std::type_index index): index(index), component(nullptr) {}
        Entry(std::type_index id, std::unique_ptr<Component> comp): index(id), component(std::move(comp)) {}
    };
    std::vector<Entry> components;

    auto find(const Entry& entry) const -> decltype(components.begin()) {
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
    Entity() = default;

    template<typename T>
    T* get() const {
        detail::is_component<T>();
        auto it = find(std::type_index(typeid(T)));

        if(it == components.end()) {
            return nullptr;
        }

        return static_cast<T*>(it->component.get());
    }

    template<typename T, typename... Args>
    void emplace(Args&&... args) {
        detail::is_component<T>();
        std::unique_ptr<Component> c{ new T(std::forward<Args>(args)...) };
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
} // fire

#include <iostream>

struct HealthComponent : fire::Component {
    int hp = 100;
};

struct PositionComponent : fire::Component {
    int x = 30;
    int y = 40;
};

int main() {
    fire::Entity lol;
    lol.emplace<HealthComponent>();
    lol.emplace<PositionComponent>();
    {
        auto component = lol.get<HealthComponent>();
        if(component) {
            std::cout << "Subtracting HP\n";
            component->hp -= 20;
            std::cout << "HP: " << component->hp << '\n';
        }
    }
}