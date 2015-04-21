#include <ecs/ecs>

auto gravity_group = ecs::create_entity_group<Gravity, Velocity>();
auto movement_group = ecs::create_entity_group<Velocity, Position>();

void gravity_system(float dt)
{
    for (auto entity : gravity_group)
    {
        entity.get_component<Velocity>() -= dt * sf::Vector2f{0, 10};
    }
}

void movement_system(float dt)
{
    for (auto entity : movement_group)
    {
        entity.get_component<Position>() += dt * entity.get_component<Velocity>();
    }
}

void create_ghost()
{
    auto entity = ecs::create_entity();
    entity.add_component<Velocity>(/* args */);
    entity.add_component<Position>(/* args */);
    ...
}
    
int main()
{
    create_ghost(); //subscribes to movement_group
    //..... game loop
        movement_system(dt);
    ...
    
    return 0;
}
