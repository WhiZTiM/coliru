#define CONSTEXPR  constexpr 

template<typename T>
CONSTEXPR T f(T x) {
    return x.get();
}

int main() {
  decltype(f(0)) b{};
  return b;
}