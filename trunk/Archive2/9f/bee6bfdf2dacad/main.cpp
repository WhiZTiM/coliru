template <typename ...Ts>
struct ABC {
  template <Ts ...>
  struct DEF {};
};

ABC<>::DEF<> c;

int main() {}