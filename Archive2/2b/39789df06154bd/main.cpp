#include <functional> // for std::less<T*>
#include <type_traits> // to remove cv qualifiers 

namespace cyne {
struct type_id_t {
public:
    template<typename T>
    friend constexpr type_id_t type_id();

    constexpr bool operator==(const type_id_t& other) const noexcept {
        return id == other.id;
    }

    bool operator<(const type_id_t& other) const noexcept {
        return compare{}(id, other.id);
    }
private:
    using signature = type_id_t();
    using compare = std::less<signature*>;
    signature* id;
    constexpr type_id_t(signature* id): id(id) {}
};

constexpr bool operator!=(const type_id_t& lhs, const type_id_t& rhs) noexcept {
    return not (lhs == rhs);
}

inline bool operator>(const type_id_t& lhs, const type_id_t& rhs) noexcept {
    return rhs < lhs;
}

inline bool operator>=(const type_id_t& lhs, const type_id_t& rhs) noexcept {
    return not (lhs < rhs);
}

inline bool operator<=(const type_id_t& lhs, const type_id_t& rhs) noexcept {
    return not (rhs < lhs);
}

template<typename T>
constexpr type_id_t type_id() {
    return &type_id<typename std::remove_cv<T>::type>;
}
} // cyne

#include <memory>
#include <vector>

namespace cyne {
struct entity {
private:
    using component_ptr = std::unique_ptr<void, void(*)(void*)>;
    struct entry {
        type_id_t index;
        component_ptr component;
        entry(type_id_t id): index(id), component{nullptr, [](void*){}} {} // used for search mainly
        entry(type_id_t id, component_ptr comp): index(id), component(std::move(comp)) {}
    };

    std::vector<entry> components;

    auto lower_bound(const entry& entry) const -> decltype(components.begin()) {
        auto first = components.begin();
        auto last  = components.end();
        decltype(first) it;
        auto count = last - first;
        while(count > 0) {
            it = first;
            auto step = count / 2;
            it += step;
            if(it->index < entry.index) {
                first = ++it;
                count -= step + 1;
            }
            else {
                count = step;
            }
        }
        return first;
    }

    bool find(const entry& entry) const {
        auto it = lower_bound(entry);
        return it != components.end() && !(entry.index < it->index);
    }

    auto find_iterator(type_id_t id) const -> decltype(components.begin()) {
        auto it = lower_bound(id);
        auto end = components.end();
        if(it != end && id < it->index) {
            return end;
        }
        return it;
    }

    template<typename T>
    bool has_impl() const {
        return find(type_id<T>());
    }

    template<typename T, typename... Args>
    typename std::enable_if<(sizeof...(Args) >= 1), bool>::type has_impl() const {
        return has_impl<T>() && has_impl<Args...>();
    }

    template<typename T>
    void remove_impl() {
        auto it = lower_bound(type_id<T>());
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
        auto&& id = type_id<T>();
        auto it = find_iterator(id);

        if(it == components.end()) {
            return nullptr;
        }

        return static_cast<T*>(it->component.get());
    }

    template<typename T, typename... Args>
    void emplace(Args&&... args) {
        auto&& id = type_id<T>();
        auto&& it = lower_bound(id);
        if(it != components.end() && !(id < it->index)) {
            return; // already inserted: no duplicates
        }
        component_ptr c{ new T(std::forward<Args>(args)...), [](void* ptr) { delete static_cast<T*>(ptr); } };
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

    auto size() const noexcept -> decltype(components.size()) {
        return components.size();
    }
};
} // cyne 

#include <type_traits>
#include <utility>
#include <iterator>
#include <tuple>

namespace cyne {
namespace detail {
// trait to check for pseudo-entity class
struct is_entity {
    struct tester {};
    template<typename T, typename X = decltype(std::declval<T>().template get<tester>()),
                         typename H = decltype(std::declval<T>().template has<tester>())>
    static std::is_same<X, tester*> test(int);
    template<typename...>
    static std::false_type test(...);
};

// trait to check if a type is iterable
struct is_iterable {
    template<typename T, typename B = decltype(begin(std::declval<T>())),
                         typename E = decltype(end(std::declval<T>())),
                         typename I = decltype(++std::declval<B>()),
                         typename D = decltype(*std::declval<B>()),
                         typename C = decltype(std::declval<B>() != std::declval<E>())>
    static std::true_type test(int);
    template<typename...>
    static std::false_type test(...);
};

template<typename T>
using raw_t = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template<typename Container>
using value_type_t = typename raw_t<Container>::value_type;

template<typename Container, typename... Components>
struct entities_with_t {
private:
    Container&& c; // this will be a collapsed reference type
    using iterator_type = decltype(begin(c));
    using entity_type = typename std::iterator_traits<iterator_type>::value_type;

    struct iterator : std::iterator<std::forward_iterator_tag, entity_type> {
    private:
        friend struct entities_with_t;
        Container&& ref;
        iterator_type it;
        iterator(Container&& ref, iterator_type it): ref(std::forward<Container>(ref)), it(it) { satisfy_predicate(); }

        void satisfy_predicate() {
            using std::end;
            auto&& last = end(std::forward<Container>(ref));
            while(it != last && not it->template has<Components...>()) {
                ++it;
            }
        }
    public:
        iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

        entity_type& operator*() const {
            return *it;
        }

        entity_type* operator->() const {
            return &*it;
        }

        iterator& operator++() {
            ++it;
            satisfy_predicate();
            return *this;
        }

        iterator operator++(int) {
            iterator copy(*this);
            this->operator++();
            return copy;
        }

        bool operator==(const iterator& other) const noexcept {
            return it == other.it;
        }

        bool operator!=(const iterator& other) const noexcept {
            return it != other.it;
        }
    };
public:
    entities_with_t(Container&& c): c(std::forward<Container>(c)) {}

    iterator begin() const {
        using std::begin;
        return { std::forward<Container>(c), begin(std::forward<Container>(c)) };
    }

    iterator end() const {
        using std::end;
        return { std::forward<Container>(c), end(std::forward<Container>(c)) };
    }
};

template<unsigned... Ns>
struct indices {};

template<unsigned N, unsigned... Ns>
struct build_indices : build_indices<N-1, N-1, Ns...> {};

template<unsigned... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};

template<typename Component>
inline bool check_component_null(Component component) noexcept {
    return component != nullptr;
}

template<typename Component, typename Other>
inline bool check_component_null(Component left, Other right) noexcept {
    return left != nullptr and right != nullptr;
}

template<typename Component, typename... Components>
inline bool check_component_null(Component left, Components... others) noexcept {
    return left != nullptr and check_component_null(others...);
}

template<typename Tuple, unsigned... Indices>
inline bool all_not_null(const Tuple& tup, indices<Indices...>) {
    // expand the tuple and call our previous function
    return check_component_null(std::get<Indices>(tup)...);
}

template<typename... Components>
inline bool all_not_null(const std::tuple<Components*...>& tup) {
    return all_not_null(tup, build_indices<sizeof...(Components)>{});
}

template<typename Container, typename... Components>
struct components_from {
private:
    Container&& c;
    using iterator_type = decltype(begin(c));
    using entity_type   = typename std::iterator_traits<iterator_type>::value_type;

    struct iterator : std::iterator<std::input_iterator_tag, std::tuple<Components*...>> {
    private:
        using tuple_type = std::tuple<Components*...>;
        friend struct components_from;

        Container&& ref;
        iterator_type it;
        tuple_type value;
        iterator(Container&& ref, iterator_type it): ref(std::forward<Container>(ref)), it(it) { satisfy_predicate(); }

        void satisfy_predicate() {
            using std::end;
            auto&& last = end(std::forward<Container>(ref));
            while(it != last) {
                value = std::make_tuple(it->template get<Components>()...);
                if(all_not_null(value)) {
                    break;
                }
                ++it;
            }
        }
    public:
        iterator() = default;
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

        const tuple_type& operator*() const {
            return value;
        }

        const tuple_type* operator->() const {
            return &value;
        }

        tuple_type& operator*() {
            return value;
        }

        tuple_type* operator->() {
            return &value;
        }

        iterator& operator++() {
            ++it;
            satisfy_predicate();
            return *this;
        }

        iterator operator++(int) {
            iterator copy(*this);
            this->operator++();
            return copy;
        }

        bool operator==(const iterator& other) const noexcept {
            return it == other.it;
        }

        bool operator!=(const iterator& other) const noexcept {
            return it != other.it;
        }
    };
public:
    components_from(Container&& c): c(std::forward<Container>(c)) {}

    iterator begin() const {
        using std::begin;
        return { std::forward<Container>(c), begin(std::forward<Container>(c)) };
    }

    iterator end() const {
        using std::end;
        return { std::forward<Container>(c), end(std::forward<Container>(c)) };
    }
};
} // detail

template<typename T>
struct is_entity : decltype(detail::is_entity::test<T>(0)) {};

template<typename T>
struct is_iterable : decltype(detail::is_iterable::test<T>(0)) {};


// /* proxy */ entities_with<Args...>(iterable)
// /* proxy */ components_from_entities(iterable)

template<typename... Components, typename Container>
inline detail::entities_with_t<Container, Components...> entities_with(Container&& c) {
    static_assert(is_iterable<Container>::value, "Container passed must be iterable (i.e. begin(c) and end(c) are valid)");
    static_assert(is_entity<detail::value_type_t<Container>>::value, "Container::value_type must be cyne::entity");
    return { std::forward<Container>(c) };
}

template<typename... Components, typename Container>
inline detail::components_from<Container, Components...> components_from(Container&& c) {
    static_assert(is_iterable<Container>::value, "Container passed must be iterable (i.e. begin(c) and end(c) are valid)");
    static_assert(is_entity<detail::value_type_t<Container>>::value, "Container::value_type must be cyne::entity");
    return { std::forward<Container>(c) };
}
} // cyne

#include <iostream>

struct health {
    int hp = 80;
};

struct other {
    int x = 20;
};

struct lol {
    int y = 30;
};

int main() {
    std::vector<cyne::entity> entities;
    entities.resize(20);
    for(unsigned i = 0; i < 20; ++i) {
        bool conds[] = { (i % 2 == 0), (i % 5 == 0), (i % 2 != 0) };
        if(i % 2 == 0) {
            entities[i].emplace<health>();
        }
        if(i % 5 == 0) {
            entities[i].emplace<lol>();
        }
        if(i % 2 != 0) {
            entities[i].emplace<other>();
        }
    }

    for(auto&& entity : cyne::entities_with<lol, other>(entities)) {
        auto x = entity.get<lol>(); 
        auto y = entity.get<other>();
        std::cout << x->y << ", " << y->x << '\n';
    }
    
    for(auto&& components : cyne::components_from<lol, other>(entities)) {
        std::cout << std::get<0>(components)->y << ", " << std::get<1>(components)->x << '\n';
    }
}
