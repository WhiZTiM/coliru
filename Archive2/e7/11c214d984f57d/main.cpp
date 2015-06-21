#include <initializer_list>
#include <type_traits>
#include <memory>
#include <string>
#include <vector>


class yaml_handler {};


class yaml_reader {
    public:
		std::vector<std::shared_ptr<yaml_handler>> handlers;

		template<class InputIterator>
		inline yaml_reader(InputIterator beg, InputIterator end);
};

template<class InputIterator>
inline yaml_reader::yaml_reader(std::enable_if_t<std::is_constructible<decltype(handlers), InputIterator, InputIterator>(), InputIterator>() beg,
                                         InputIterator end) : handlers(beg, end) {}

template<class InputIterator>
inline yaml_reader::yaml_reader(std::enable_if_t<std::is_constructible<decltype(handlers),
                                                          std::add_pointer_t<std::result_of_t<decltype(std::declval<InputIterator>()->copy)())>,
                                                          std::add_pointer_t<std::result_of_t<decltype(std::declval<InputIterator>()->copy)())>>(), InputIterator> beg,
                                         InputIterator end) {
	handlers.reserve(std::distance(beg, end));
	std::transform(beg, end, std::back_inserter(handlers), [&](const auto & handler) {
		return handler.copy();
	});
}

int main() {
    vector<yaml_handler> hndlr(20);
	yaml_reader reader(hndlr.begin(), hndlr.end());
}
