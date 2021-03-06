#include <chrono>
#include <iostream>
#include <mutex>     // std::mutex
#include <thread>    // std::thread


void print_block(int n, char c)
{
    while( n-- )
	{
		std::cout << c;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	std::cout << '\n';
}

std::mutex mtx;           // mutex for critical section

void print_critial_block(int n, char c)
{
	// entering critical section
	mtx.lock();
	while( n-- )
	{
		std::cout << c;
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	std::cout << '\n';
	mtx.unlock();
    // leaving critical section
}

int main()
{
	{
	std::thread th1(print_block, 40, '*');
	std::thread th2(print_block, 40, '$');

	th1.join();
	th2.join();
	}

	std::cout << "=== next run ===========================+\n";
	{
	std::thread th1(print_critial_block, 40, '*');
	std::thread th2(print_critial_block, 40, '$');

	th1.join();
	th2.join();
	}
	return 0;
}
