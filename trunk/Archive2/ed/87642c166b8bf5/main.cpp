#include <set>
#include <string>
#include <stdexcept>
#include <iostream>

#include <boost/iterator/zip_iterator.hpp>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/range.hpp>

template <typename... T>
auto zip(const T&... containers) -> boost::iterator_range<boost::zip_iterator<decltype(boost::make_tuple(std::begin(containers)...))>>
{
    auto zip_begin = boost::make_zip_iterator(boost::make_tuple(std::begin(containers)...));
    auto zip_end = boost::make_zip_iterator(boost::make_tuple(std::end(containers)...));
    return boost::make_iterator_range(zip_begin, zip_end);
}

template<typename T>
auto numeric_range(T min, T max) {
    return boost::make_iterator_range(
        boost::counting_iterator<T>(min),
        boost::counting_iterator<T>(max)
    );
}

template<typename T>
auto zipWithIndex (T const& r) {
    return zip(numeric_range(0, int(r.size())), r);
}

int main() {
    std::set<std::string> m = { "bartek", "sehe", "kbok" };
 
    for (auto const& e : zipWithIndex(m)) {
        std::cout << boost::get<0>(e) << ": " << boost::get<1>(e) << std::endl;
    }
}
