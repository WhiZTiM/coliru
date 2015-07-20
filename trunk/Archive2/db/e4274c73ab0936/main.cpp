#include <array>

template<class T, std::size_t n>
class Vector {
  std::array<T, n> elements;

public:
  Vector();
  explicit Vector(std::array<T, n>& elements_);
  Vector(const Vector<T, n>& v);
  explicit Vector(Vector<T, n>&& v);
  ~Vector() noexcept = default;
  Vector<T, n>& operator =(const Vector<T, n>& v);
  Vector<T, n>& operator =(Vector<T, n>&& v);
  T& operator [](std::size_t i);
};

template<class T, class... Ts>
Vector<T, sizeof...(Ts) + 1> make_vector(T v, Ts... args) {
    const std::size_t n = sizeof...(Ts) + 1;
    std::array<T, n> vals = {v, args...};
    return Vector<T, n>{vals};
}

int main()
{
   auto v{make_vector<int>(0, 1, 2, 3)};
}