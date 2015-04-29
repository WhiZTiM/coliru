#include <algorithm>
#include <memory>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

class Entity
{
    int a;
};

class Terrain : public Entity
{
    int b;
};

class Grass : public Terrain
{
    int c;
};

int main()
{
    Entity* a = new Grass;
    return 0;
}
