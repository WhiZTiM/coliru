#include <type_traits>
#include <vector>
#include <tuple>

template <typename ... IteratorTypes>
void foo(IteratorTypes&&...its)
{
    using ValueTypes = typename std::iterator_traits<IteratorTypes...>::value_type;
	static_assert(std::is_same<std::tuple<ValueTypes>,std::tuple<int,float>>::value, "types do no match");
}

int main() {
	std::vector<int> int_vec(1);
	std::vector<float> float_vec(1);
	
	foo(int_vec.begin(), float_vec.begin());
	return 0;
}