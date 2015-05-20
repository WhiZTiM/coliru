#include <iostream>
#include <string>
#include <memory>
#include <algorithm>

template <typename OutputIt>
auto make_raw_storage_iterator( OutputIt out ) {
    return std::raw_storage_iterator<OutputIt, std::remove_pointer_t<decltype(&*out)>>(out);
}

int main()
{
    const std::string s[] = {"This", "is", "a", "test", "."};
    std::string* p = std::get_temporary_buffer<std::string>(5).first;

    std::copy(std::begin(s), std::end(s),
              make_raw_storage_iterator(p));

    for(std::string* i = p; i!=p+5; ++i) {
        std::cout << *i << '\n';
        i->~basic_string<char>();
    }
    std::return_temporary_buffer(p);
}
