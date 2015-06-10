#include <iostream>
#include <memory>
#include <vector>
#include <type_traits>

struct ComponentBase {
    virtual ~ComponentBase() = default;
};

struct Entity {
    template<typename Component, typename... Args>
    auto set(Args&&... args) -> std::enable_if_t<std::is_constructible<Component, Entity&, Args...>::value> {
        _components.push_back(std::make_unique<Component>(*this, std::forward<Args>(args)...));
    }

    template<typename Component, typename... Args>
    auto set(Args&&... args) -> std::enable_if_t<std::is_constructible<Component, Args...>::value> {
        _components.push_back(std::make_unique<Component>(std::forward<Args>(args)...));
    }

    std::vector<std::unique_ptr<ComponentBase>> _components;
};

struct DelicateFlower : ComponentBase {
    DelicateFlower(int, std::string, float) {
        std::cout << "A delicate flower" << std::endl;
    }
};

struct PreciousSnowflake : ComponentBase {
    PreciousSnowflake(Entity&, int, std::string, float) {
        std::cout << "A precious snowflake" << std::endl;
    }
};

int main() {
    Entity e;

    e.set<DelicateFlower>(1, "hi", 2.0);
    e.set<PreciousSnowflake>(1, "hi", 2.0);
}
