#include <utility>
#include <string>

std::tuple<int, std::string, char> foo() {
    return {1, "faagel", 'c'};
}

int main() {
    auto ret = foo();
}
