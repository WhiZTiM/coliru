#include <vector>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/range.hpp>
#include <tuple>
#include <iostream>
#include <iterator>
#include <algorithm>



using namespace std;

/*
template<typename Iter, typename Pred>
auto Sorted(Iter first, Iter last, Pred p) -> std::vector<typename std::iterator_traits<Iter>::value_type>
{
    typedef  typename std::iterator_traits<Iter>::value_type Type;
	std::vector<Type> filtered;
	filtered.reserve(std::distance(first, last));
	std::copy_if(first, last, std::back_inserter(filtered), p);
	std::sort(filtered.begin(), filtered.end());
	return filtered;
}
*/

template<typename Cont>
auto Zip(Cont const& l, Cont const& r) //-> boost::iterator_range<boost::zip_iterator<decltype(boost::make_tuple(std::begin(l)))>> :-) Could not got around the return type. Just say auto in C++14 and later. he he.....
{
	auto zip_begin = boost::make_zip_iterator(boost::make_tuple(l.begin(), r.begin()));
	auto zip_end = boost::make_zip_iterator(boost::make_tuple(l.end(), r.end()));
	return boost::make_iterator_range(zip_begin, zip_end);
}

void ByPopularDemand(std::vector<int> source)
{
    std::vector<int> odds; odds.reserve(source.size());
    std::vector<int> evens;  evens.reserve(source.size());
    
    auto oddFilter = [](int x) { return x % 2 == 1; };
    auto evenFilter = [](int x) { return x % 2 == 0; };
    
    std::copy_if(source.begin(), source.end(), std::back_inserter(odds), oddFilter);
    std::copy_if(source.begin(), source.end(), std::back_inserter(evens), evenFilter);
    
	if (odds.size() != evens.size())
		return;

	int x, y;
	   
    for (auto tup : Zip(odds, evens))
	{
		boost::tie(x, y) = tup;
        std::cout << x << "," << y << ",";
	}
	std::cout << "\n";    
}

void ArrangeArrayTest()
{
	ByPopularDemand({ 1, 2, 3, 4 });
	ByPopularDemand({ 2, 1, 3, 4 });
	ByPopularDemand({ 1, 2, 4, 4 });
	ByPopularDemand({ 4, 3, 2, 5 });
}


int main()
{
    ArrangeArrayTest();
}