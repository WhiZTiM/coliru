#include <iostream>
#include <map>
#include <memory>

typedef std::map<
    uint32_t, std::map<
        uint32_t, std::map<uint32_t, std::pair<uint32_t, uint32_t> > >
> Lookup;

const uint32_t TERRAIN_TYPE_GRASS = 0;
const uint32_t TERRAIN_TYPE_SAND = 1;
const uint32_t TERRAIN_TYPE_WATER = 2;
const uint32_t TERRAIN_TYPE_FOREST = 4;
const uint32_t TERRAIN_TYPE_ROCK = 8;

Lookup& get_lookup() {
    static std::shared_ptr<Lookup> lookup;
    if(!lookup) {
        lookup = std::make_shared<Lookup>();

        Lookup& ref = *lookup;

        ref[TERRAIN_TYPE_GRASS][0U][0U] = std::make_pair(0, 0);
        ref[TERRAIN_TYPE_SAND][0U][0U] = std::make_pair(1, 0);
        ref[TERRAIN_TYPE_WATER][0U][0U] = std::make_pair(2, 0);
        ref[TERRAIN_TYPE_FOREST][0U][0U] = std::make_pair(3, 0);
        ref[TERRAIN_TYPE_ROCK][0U][0U] = std::make_pair(4, 0);
    }
    return *lookup;
}

int main() {
    Lookup& ref = get_lookup();

    std::cout << ref[8U][0U][0U].first << ' ' << ref[8U][0U][0U].second << std::endl;
    std::cout << ref[8U][8U][8U].first << ' ' << ref[8U][8U][8U].second << std::endl;
}
