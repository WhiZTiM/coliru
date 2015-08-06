
#include <iostream>
#include <vector>
#include <list>
using namespace std;

template <template <template <class, class...> class> class Make, class T>
struct make_with_container {};

template <template <template <class, class...> class> class Make, template<class, class...> class Container, class T>
struct make_with_container<Make, Container<T>> {
  typedef Make<Container> type;
};

template <template <class, class...> class Container>
struct SampleData {
  Container<float> totalradiance;
  Container<int> lightcutSize;

  template <class Fun>
  auto make(Fun make)
    -> typename make_with_container<SampleData, decltype(make(totalradiance))>::type
  {
    return {
       make(totalradiance   )
     , make(lightcutSize    )
    	};
	}
};

struct converter
{
	template <class T>
	::std::list<T> operator()(::std::vector<T>& v)
	{
		return ::std::list<T>(v.begin(), v.end());
	}
};

int main() {
	SampleData<::std::vector> samples;

	SampleData<::std::list> const converted = samples.make(converter());

	return 0;
}
