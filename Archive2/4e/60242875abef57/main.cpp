#include <algorithm>
#include <iterator>

template <typename InputIt, typename OutputIt, typename Locale>
OutputIt tolower (InputIt first, InputIt last, OutputIt out, Locale const& locale) {
    auto func = [facet = &std::use_facet<std::ctype<typename std::iterator_traits<InputIt>::value_type>>(locale)] (auto ch) {
        return facet->tolower(ch);
    };
    return std::transform(first, last, out, func);
}

#include <iostream>
int  main() {
    std::string str = "Hello world!";
    tolower(str.begin(), str.end(), std::ostreambuf_iterator<char>(std::cout), std::locale());
}