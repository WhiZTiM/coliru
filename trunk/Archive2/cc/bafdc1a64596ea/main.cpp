#include <memory>

using std::shared_ptr;

shared_ptr<int> f() {
    return shared_ptr<int>{new int(42)};
}

int main() {
    f();
}
