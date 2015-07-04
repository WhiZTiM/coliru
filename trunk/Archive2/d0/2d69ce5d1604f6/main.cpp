#include <utility>
#include <iostream>

class Foo {
public:
    Foo(int* texture) {
        texture = std::make_shared(texture);
    }

    Foo(std::shared_ptr<int> texture) {
        texture = texture;   
    }
        
    Foo(const Foo& other) :
        texture(other.texture) {}
        
    int* get() {
        return texture.get()   
    }
private:
    std::shared_ptr<int> texture;
};

int main() {
    Foo f(new int(5));
    
    std::cout << f.get() << std::endl; 
}