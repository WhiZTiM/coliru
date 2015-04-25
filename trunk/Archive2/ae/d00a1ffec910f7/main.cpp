#include <unordered_map>
#include <typeindex>
#include <list>
#include <functional>
#include <vector>
#include <memory>
#include <tuple>
#include <algorithm>
#include <iostream>
#include <type_traits>

    class world {
    private:

        class entity {
        public:
            
            // construction
            entity() = default;
            entity(entity const&) = delete;
            entity(entity&&) = default;

            // assignment
            entity& operator=(entity const&) = delete;
            entity& operator=(entity&&) = default;

            // component query
            template<typename Component, typename... Components>
            bool has() const {
                return has<Component>() && has<Components...>();
            }
            
            template<typename Component>
            bool has() const {
                auto it = components.find(std::type_index(typeid(Component)));
                return it != components.end();
            }

            // component access
            template<typename Component>
            Component& get() {
                auto it = components.find(std::type_index(typeid(Component)));
                return *static_cast<Component*>(it->second.get());
            }

            // component addition
            template<typename Component, typename... Args>
            void add(Args&&... args) {
                auto component_deleter
                    = [](void* ptr) { delete static_cast<Component*>(ptr); };
                components.emplace
                    ( std::type_index(typeid(Component))
                    , component_type
                        ( new Component(std::forward<Args>(args)...)
                        , component_deleter ));
            }

            // component removal
            template<typename Component>
            void remove() {
                components.erase(std::type_index(typeid(Component)));
            }

        private:

            // attributes
            using component_type = std::unique_ptr<void, void(*)(void*)>;
            std::unordered_map<std::type_index, component_type> components;

        };
        
    public:

        // exported types
        using behavior = std::function<void(world&)>;
        using entity_ref = std::list<entity>::iterator;
        using iterator = std::list<entity>::iterator;
        using const_iterator = std::list<entity>::const_iterator;

        // exceptions
        struct stop : std::exception {};

        // construction
        world() = default;
        world(std::initializer_list<behavior> bs)
            : behaviours(bs)
            {}

        world(world const&) = delete;
        world(world&&) = default;

        // assignment
        world& operator=(world const&) = delete;
        world& operator=(world&&) = default;

        // entity management
        entity_ref create() {
            // @todo: not concurrent safe
            entities.push_front(entity());
            return entities.begin();
        }
        
        template<typename... Components>
        void transform(std::function<void(Components...)> fn) {
            for (auto& e : entities) {
                if (e.has<std::remove_reference_t<Components>...>())
                    fn(e.get<std::remove_reference_t<Components>>()...);
            }
        }

        // entity destruction
        void kill(entity_ref entity) {
            entities.erase(entity);
        }

        // world status management
        void start() {
            while (true) {
                try {
                    for (auto& behaviour : behaviours)
                        behaviour(*this);
                } catch (stop const&) {
                    break;
                }
            }
        }

        // container traversal
        iterator begin() { return entities.begin(); }
        iterator end() { return entities.end(); }
        const_iterator begin() const { return entities.begin(); }
        const_iterator end() const { return entities.end(); }
        const_iterator cbegin() const { return entities.cbegin(); }
        const_iterator cend() const { return entities.cend(); }

    private:

        // attributes
        std::vector<behavior> behaviours;
        std::list<entity> entities;

    };
    
struct abc { int x; abc(int a) : x(a) {} };
struct def { int x; def(int a) : x(a) {} };
struct ghc { int x; ghc(int a) : x(a) {} };
        
int main() {
    world w{};
    
    auto e1 = w.create();
    e1->add<abc>(123);
    e1->add<def>(234);
    
    auto e2 = w.create();
    e2->add<abc>(123);
    e2->add<ghc>(234);

    w.transform<abc&, ghc&>([](abc& a, ghc& b) {
        std::cout << a.x << ' ' << b.x;
    });
}