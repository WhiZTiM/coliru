#include <iostream>
#include <vector>

class Id {
public:
    Id(std::size_t id) : inner(id) {}
    
    template<typename Container>
    friend typename Container::value_type& access(Container& container, Id index) {
        return container[index.inner];
    }
private:
    std::size_t inner;
};

int main()
{
    auto ix = Id(2);
    std::vector<int> vector{1, 2, 3, 4};
    std::cout << access(vector, ix);
}