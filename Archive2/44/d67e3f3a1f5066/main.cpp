#include <iostream>
#include <algorithm>
#include <array>
#include <functional>

int main() {
    std::array<int, 7> array{{1, 2, 3, 4, 5, 6, 7}};
    int a = 0;
    int b = 0;
    std::cout << "Input range as `a b` for [a, b]:\n";
    std::cin >> a >> b;
    std::cout << a << ' ' << b << '\n';
    std::transform(begin(array) + a, begin(array) + b + 1, (begin(array) + a), [](int x) { return x + 1; });
    std::copy(begin(array), end(array), std::ostream_iterator<int>(std::cout, " "));
}
