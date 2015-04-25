#include <memory>
#include <unordered_map>
#include <typeindex>
#include <iostream>

        class entity {
        public:

            // component access
            template<typename Component>
            Component& get() {
                return *static_cast<Component*>
                    (components[std::type_index(typeid(Component))].get());
            }

            // component addition
            template<typename Component, typename... Args>
            void add(Args&&... args) {
                components[std::type_index(typeid(Component))]
                    = component_type
                        ( new Component(std::forward<Args>(args)...)
                        , [](void* ptr) { delete static_cast<Component*>(ptr); } );
            }

        private:

            // attributes
            using component_type = std::unique_ptr<void, void(*)(void*)>;
            std::unordered_map<std::type_index, component_type> components;

        };
        
struct pos { int x, y; pos(int a, int b) : x(a), y(b) {} };
        
int main() {
    entity x{};
    x.add<pos>(1, 2);
    std::cout << x.get<pos>().x;
}