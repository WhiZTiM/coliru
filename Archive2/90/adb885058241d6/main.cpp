
auto g(int)->int{return {};}

auto f(auto (*)(int)->int) -> void {}

int main() {
  f(g);
}