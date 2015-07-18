template<int S>
struct array {
  static_assert(S != 1);
  void size() const;
};

template<typename... Ts>
using array_u = array<sizeof...(Ts)>;

template <typename ...Ts>
void foo()
{
  array_u<Ts...> a1;
}
