#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <random>
#include <chrono>

template <typename Iterator, typename Compare = std::less<typename Iterator::value_type>>
void merge_sort(Iterator begin, Iterator end, Compare comp = Compare{})
{
    if (begin == end || std::next(begin) == end) return;

	auto length = std::distance(begin, end);
	
	if (length <= 100)
	{
		for (auto i = begin; i != end; ++i) 
		{
        	std::rotate(std::upper_bound(begin, i, *i), i, std::next(i));
    	}
		return;
	}

	auto middle = begin;	
	std::advance(middle, length / 2);

	merge_sort(begin, middle, comp);
	merge_sort(middle, end, comp);

	std::inplace_merge(begin, middle, end);
}

template <typename Iterator, typename Compare = std::less<typename Iterator::value_type>>
void parallel_merge_sort(Iterator begin, Iterator end, int threads = std::thread::hardware_concurrency(), Compare comp = Compare{})
{
	if (begin == end || std::next(begin) == end) return;

	auto length = std::distance(begin, end);

	if (length <= 100)
	{
		for (auto i = begin; i != end; ++i) 
		{
            std::rotate(std::upper_bound(begin, i, *i), i, std::next(i));
    	}
		return;
	}

	auto middle = begin;	
	std::advance(middle, length / 2);

	if (threads > 0)
	{
		std::thread thread{parallel_merge_sort<Iterator>, begin, middle, threads/2 - 1, comp};
		parallel_merge_sort(middle, end, threads/2 - 1, comp);
        thread.join();
	}
	else
	{
    	merge_sort(begin, middle, comp);
        merge_sort(middle, end, comp);
	}
	
	std::inplace_merge(begin, middle, end);
}

int main()
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1,100000);

	std::vector<int> v;
	v.reserve(10000000);
	for (int i = 0; i < 10000000; ++i)
	{
		v.push_back(distribution(generator));
	}

	auto start = std::chrono::high_resolution_clock::now();
    
	parallel_merge_sort(v.begin(), v.end(), 6);
	
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration<double, std::milli>(end - start).count() << std::endl;

	return 0;
}
	
