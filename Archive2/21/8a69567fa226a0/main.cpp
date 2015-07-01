#include <iostream>
#include <unordered_map>

struct vao_maker_attribute {
    std::string name;
    
    template<class T>
    vao_maker_attribute(std::string name, T) {
    }
};

struct vao {
    vao(std::initializer_list<vao_maker_attribute> attr) {
    }
};

int main() {
    auto my_vao = vao{{"position", std::declval<float>()}, {"normal", std::declval<float>()}};
}