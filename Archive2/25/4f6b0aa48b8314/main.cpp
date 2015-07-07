#include <iostream>
#include <bitset>

struct Wheel {
    Wheel(int size)
    : _size(size)
    , _onePos(0) {}
    
    void rotate() {
        ++_onePos;
        if(_onePos == _size) {
            _onePos = 0;
            onFullRotation();
        }
    }
    
    unsigned int bits() const {
        return 1u << _onePos;
    }
    
private:
    void onFullRotation() {
        std::cout << "<full rotation>";
    }
    
    int const _size;
    int _onePos;
};

int main() {
    Wheel w(5);
    
    for(int i = 0; i < 10; ++i) {
        w.rotate();
        std::cout << std::bitset<5>(w.bits()) << '\n';
    }
}