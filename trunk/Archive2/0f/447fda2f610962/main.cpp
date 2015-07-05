#include <future>
#include <thread>
#include <chrono>
#include <iostream>

void f()
{
    std::cout << "f()\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "f() done\n";
}

void g()
{
	std::cout << "g()\n";
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "g() done\n";
}

int main()
{
	std::async(std::launch::async, f); //run sequentially
	std::async(std::launch::async, g);

	auto f1 = std::async(std::launch::async, f); //launched in parallel,
	auto f2 = std::async(std::launch::async, g); //still blocked at the end of main() though

	std::cout << "main() done\n";
}
