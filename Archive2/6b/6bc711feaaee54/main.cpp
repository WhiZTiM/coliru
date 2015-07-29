#include <unordered_map>

struct X {
  X(bool) {}
  X(X const&) = delete;
  const X& operator=(X const&) = delete;
};

typedef std::unordered_map<int,X> Map;

int main() {
  Map m;
  m.emplace(std::piecewise_construct, std::forward_as_tuple( 1 ), std::forward_as_tuple( true ) );
  return 0;
}
