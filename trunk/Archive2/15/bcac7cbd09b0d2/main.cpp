#include <memory>

using std::shared_ptr;

shared_ptr<int> f(int i) {
    switch(i) {
    case 0:
        return new int(42); // Error
    case 1:
        return {new int(42)};// Error
    default:
        return shared_ptr<int>{new int(42)};
    }
}

int main() {
    f(0);
}
