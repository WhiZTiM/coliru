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
		std::thread thread{ parallel_merge_sort<Iterator>, begin, middle, threads / 2 - 1, comp };
		parallel_merge_sort(middle, end, threads / 2 - 1, comp);
		thread.join();
	}
	else
	{
		merge_sort(begin, middle, comp);
		merge_sort(middle, end, comp);
	}
	std::inplace_merge(begin, middle, end);
}

template <typename Iterator>
void print_collection(Iterator start, Iterator end)
{
	for (auto i = start; i != end; i++)
	{
		std::cout << *i << " ";
	}
	std::cout << std::endl;
}

std::vector<int> make_random_vector(const int size)
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 10000);
	std::vector<int> v;
	v.reserve(size);
	for (int i = 0; i < size; ++i)
	{
		v.push_back(distribution(generator));
	}
	return v;
}

void run_parallel_sort_test(const int size)
{
	std::vector<int> v(make_random_vector(size));
	auto start = std::chrono::high_resolution_clock::now();
	parallel_merge_sort(v.begin(), v.end());
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Parallel for size " << size << ": " << std::chrono::duration<double, std::milli>(end - start).count() << std::endl;
}

void run_serial_sort_test(const int size)
{
	std::vector<int> v(make_random_vector(size));
	auto start = std::chrono::high_resolution_clock::now();
	merge_sort(v.begin(), v.end());
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "Serial for size " << size << ": " << std::chrono::duration<double, std::milli>(end - start).count() << std::endl;
}

int main()
{
	run_serial_sort_test(1000);
	run_parallel_sort_test(1000);
	run_serial_sort_test(10000);
	run_parallel_sort_test(10000);
	run_serial_sort_test(100000);
	run_parallel_sort_test(100000);
	run_serial_sort_test(1000000);
	run_parallel_sort_test(1000000);
	run_serial_sort_test(10000000);
	run_parallel_sort_test(10000000);
	run_serial_sort_test(100000000);
	run_parallel_sort_test(100000000);
	return 0;
}
