#include <boost/multi_array.hpp>
#include <iostream>

int main() {
    using namespace boost;
    using MA = multi_array<double, 2>;

    MA ma(extents[12][34]);
    auto& ma_shape = reinterpret_cast<boost::array<size_t, MA::dimensionality> const&>(*ma.shape());

    // demo
    std::cout << "[" << ma_shape[0] << "][" << ma_shape[1] << "]\n";

    // resize
    MA other;
    assert(!std::equal(ma_shape.begin(), ma_shape.end(), other.shape()));

    other.resize(ma_shape);
    assert(std::equal(ma_shape.begin(), ma_shape.end(), other.shape()));

    // reshape
    other.resize(extents[1][12*34]);
    assert(!std::equal(ma_shape.begin(), ma_shape.end(), other.shape()));

    other.reshape(ma_shape);
    assert(std::equal(ma_shape.begin(), ma_shape.end(), other.shape()));
}
