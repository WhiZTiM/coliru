#include <iostream>
#include <memory>
#include <assert.h>

using u16_t = unsigned short int;
using u32_t = unsigned int;

using f32_t = float;

struct vec2s {
    u16_t x;
    u16_t y;
    
    vec2s() = default;

    explicit vec2s(u16_t my_x, u16_t my_y) : x(my_x), y(my_y) {
        
    }
};

class Matrix {
private:
    u16_t _width;
    u16_t _height;

    std::unique_ptr<u32_t> _data;

public:
    explicit Matrix(u16_t width, u16_t height) : _width(width), _height(height) {
        const u32_t size = _width * _height;

        _data = std::make_unique<u32_t>(size);

        for (u32_t i = 0; i < size; i++) {
            _data.get()[i] = 0;
        }
    }
    
    Matrix(const Matrix&) = delete;

    u16_t width() const {
        return _width;
    }

    u16_t height() const {
        return _height;
    }

    u32_t& operator [](const vec2s& vec) {
        assert(vec.x < _width && vec.y < _height);
        return _data.get()[vec.x * _width + vec.y];
    }

    u32_t operator [](const vec2s& vec) const {
        assert(vec.x < _width && vec.y < _height);
        return _data.get()[vec.x * _width + vec.y];
    }

    friend std::ostream& operator <<(std::ostream& out, Matrix& m) {
        const u32_t size = m._width * m._height;
        
        for (u32_t i = 0, x = 0; i < size; i++, x++) {
            out << m._data.get()[i] << ',';
            if (x >= m._width) {
                x = 0;
                out << std::endl;
            } else {
                out << "\t";
            }
        }
        
        return out;
    }
};

int main() {
    Matrix m2(16, 16);
    m2[vec2s(1, 0)] = 42;
    m2[vec2s(0, 16)] = 43;
}