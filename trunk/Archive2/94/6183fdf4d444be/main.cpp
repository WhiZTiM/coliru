#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <random>
#include <chrono>

template <typename Iterator, typename Compare = std::less<typename Iterator::value_type>>
void parallel_merge_sort(Iterator begin, Iterator end, Compare comp = Compare{})
{
    if (begin == end || std::next(begin) == end) return;

	auto middle = begin;	
	std::advance(middle, std::distance(begin, end) / 2);

	std::thread thread;

	if (std::thread::hardware_concurrency())
	{
		thread = std::thread{&parallel_merge_sort<Iterator>, begin, middle, comp};
	}
	else
	{
		parallel_merge_sort(begin, middle, comp);
	}

	parallel_merge_sort(middle, end, comp);

	if (thread.joinable()) thread.join();

	std::inplace_merge(begin, middle, end);
}


int main()
{
 	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1,10000);

	std::vector<int> v;
	v.reserve(10000);
	for (int i = 0; i < 10000; ++i)
	{
		v.push_back(distribution(generator));
	}

	auto start = std::chrono::high_resolution_clock::now();
    
	parallel_merge_sort(v.begin(), v.end());
	
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::chrono::duration<double, std::milli>(end - start).count() << std::endl;
    
	return 0;
}
	
