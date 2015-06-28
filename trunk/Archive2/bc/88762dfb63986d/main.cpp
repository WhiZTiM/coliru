#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>
#include <ctime>
#include <time.h> 
#include <iomanip>
#include <thread>

std::vector<double> global_result;

//Kahan summation algorithm
double ksum(const std::vector<double> &data)
{
    double compensation = 0;
	double sum = 0;
	std::vector<double>::size_type index = data.size();
	while (index--)
	{
		double x = data[index] - compensation;
		double y = sum + x;
		compensation = (y - sum) - x;
		sum = y;
	}
	return sum;
}

void sum(uint64_t iter)
{
	time_t start = time(0);
	double time_passed;

	double sum = 0;
	double last_sum = 0;				 // Sum from previouse runs
	double goal = 40;					 // Original goal was 40
	unsigned int start_time = 0;		 // Time from previouse runs
	uint64_t starting_iteration = (iter * 100000000U) - 100000000U + 1; // Iteration previouse runs
	uint64_t end = iter * 100000000U;

	std::vector<double> result;
	std::vector<double> newResult;

	if (last_sum > 0)
		result.push_back(last_sum);

	// accumulate iterable into partial sums
	for (uint64_t i = starting_iteration; i < end; ++i)
	{
		double x = 1.0 / (double)i;

		for (auto &y : result)
		{
			if (x < y)
				std::swap(x, y);

			double high = x + y;
			double low = y - (high - x);

			if (low)
				newResult.push_back(low);

			x = high;
		}
		newResult.push_back(x);
		swap(result, newResult);

		//print every 10 million iterations, adding new counter that counts to 10 mil and checking if its bigger than const 10mil would maybe be faster?
		/*if (0U == (i % 10000000U))
		{
			sum = ksum(result);
			time_passed = difftime(time(0), start) + start_time;
			std::cout << std::fixed << std::setprecision(15) << "Iteration " << 1 << ": " << sum
				<< "   " << std::setprecision(1) << "sec: " << time_passed
				<< "  min: " << time_passed / 60
				<< "  h: " << time_passed / 3600 << std::endl;
		}*/
		
		newResult.clear();
	}
//	global_result.push_back(ksum(result));
	std::cout << "iter " << iter - 1 << ": " << ksum(result) << std::endl;
	global_result[iter-1] = ksum(result);
}


int main()
{
	size_t numOfThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> threads;
	threads.resize(numOfThreads);
	global_result.resize(numOfThreads);

	std::cout << "Create " << numOfThreads << " threads..." << std::endl;
	for (int i = 0; i < numOfThreads; ++i)
		threads[i] = std::thread(sum, i+1);

	std::cout << "Synchronizing all threads...\n";
	for (auto& th : threads)
		th.join();

	for (int i = 0; i < numOfThreads; ++i)
		std::cout << "Result of iteration(" << i << "): " << global_result[i] << std::endl;
	std::cout << "\nGlobal Result: "<< ksum(global_result) << std::endl;
}
