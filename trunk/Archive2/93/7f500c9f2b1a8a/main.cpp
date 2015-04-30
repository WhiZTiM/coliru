#include <iostream>
#include <map>

typedef std::map<
    uint32_t, std::map<
        uint32_t, std::map<uint32_t, std::pair<uint32_t, uint32_t> > >
> Lookup;

int main() {
    Lookup ref;
    ref[0U][0U][0U] = std::make_pair(0, 0);
    ref[1U][0U][0U] = std::make_pair(1, 0);
    ref[2U][0U][0U] = std::make_pair(2, 0);
    ref[4U][0U][0U] = std::make_pair(3, 0);
    ref[8U][0U][0U] = std::make_pair(4, 0);

    std::cout << ref[8U][0U][0U].first << ' ' << ref[8U][0U][0U].second << std::endl;
    std::cout << ref[8U][8U][8U].first << ' ' << ref[8U][8U][8U].second << std::endl;
}
