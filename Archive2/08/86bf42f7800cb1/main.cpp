#include <iostream>
#include <vector>
#include <range/v3/all.hpp>

using namespace ranges;

int main() {
    std::vector<std::string> positions = {"1a", "1b", "1c", "2a", "2b", "2c", "3a", "3b", "3c"};
    std::vector<std::string> normals = {"1d", "1e", "1f", "2d", "2e", "2f", "3d", "3e", "3f"};
    std::vector<std::string> interpolated = view::join(view::zip_with(view::concat, positions | view::chunk(3), normals | view::chunk(3)));
    for(auto s : interpolated) {
        std::cout << s << " ";
    }
    //Expected output is
    // 1a 1b 1c 1d 1e 1f 2a 2b 2c 2d 2e ... and so forth
    return 0;
}