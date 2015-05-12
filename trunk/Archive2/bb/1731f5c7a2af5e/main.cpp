#include <iostream>
#include <numeric>
#include <cmath>

auto mean = [](const auto& c) {
    return std::accumulate(begin(c), end(c), 0.) / c.size();
};

auto stddev = [](const auto& c) {
    auto sum = std::accumulate(begin(c), end(c), 0., [average = mean(c)](const auto& init, const auto& elem) {
        auto diff = (elem - average);
        return init + (diff * diff);
    });
    auto variance = sum / c.size();
    return std::sqrt(variance);
};

int main() {
    // poor main has to return int
    auto input = { 809, 816, 833, 849, 851, 961, 976, 1009, 
                   1069, 1125, 1161, 1172, 1178, 1187, 1208, 
                   1215, 1229, 1241, 1260, 1373 };
    std::cout << stddev(input) << '\n';
    return 0;
}