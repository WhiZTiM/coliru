#include <vector>
#include <algorithm>
#include<functional>
#include <type_traits>
using namespace std;
template <typename InputIterator, typename Func>
double MedianEx(InputIterator src_begin, InputIterator src_end,
    Func func) {
	using U = typename std::iterator_traits<InputIterator>::value_type;


	size_t count = std::distance(src_begin, src_end);
	sort(src_begin, src_end, [&](U a, U b) { return func(a) < func(b); });

	double median;

	if (count % 2 == 0)
		median = (func(*(src_begin + (count / 2 + 1))) +
		func(*(src_begin + (count / 2)))) /
		2.f;
	else
		median = func(*(src_begin + (count / 2)));

	return median;
}

int main()
{
	std::vector<int> arr;
	MedianEx(arr.begin(), arr.end(), [](int value){return value; });
    //MedianEx(arr.begin(), arr.end(), [](std::string value){return value; });//error


}